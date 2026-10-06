using System;
using System.IO;
using System.Text;

namespace ImageMetadataViewer.Infrastructure.Parsers
{

    public class PngParser : IImageParser
    {
        private static readonly byte[] Signature = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

        public string FormatName => "PNG";

        public bool MatchesSignature(byte[] headerPeek)
        {
            if (headerPeek.Length < 8) return false;
            for (int i = 0; i < 8; i++)
                if (headerPeek[i] != Signature[i]) return false;
            return true;
        }

        public ImageMetadata Parse(string filePath, long fileSizeBytes, Stream stream)
        {
            var result = new ImageMetadata
            {
                FileName = Path.GetFileName(filePath),
                FilePath = filePath,
                FileSizeBytes = fileSizeBytes,
                Format = FormatName
            };

            stream.Seek(8, SeekOrigin.Begin); 

            byte[] ihdrLenType = ByteReader.ReadExact(stream, 8, "заголовок чанка IHDR");
            uint ihdrLen = ByteReader.ReadUInt32BE(ihdrLenType, 0);
            string ihdrType = Encoding.ASCII.GetString(ihdrLenType, 4, 4);

            if (ihdrType != "IHDR" || ihdrLen < 13)
            {
                result.IsCorrupted = true;
                result.ErrorMessage = "Первый чанк PNG не является корректным IHDR.";
                return result;
            }

            byte[] ihdr = ByteReader.ReadExact(stream, 13, "данные чанка IHDR");
            stream.Seek((int)ihdrLen - 13 + 4, SeekOrigin.Current); 

            int width = ByteReader.ReadInt32BE(ihdr, 0);
            int height = ByteReader.ReadInt32BE(ihdr, 4);
            byte bitDepth = ihdr[8];
            byte colorType = ihdr[9];
            byte compressionMethod = ihdr[10];
            byte interlaceMethod = ihdr[12];

            result.WidthPx = width;
            result.HeightPx = height;
            result.ColorDepthBits = bitDepth * ChannelsForColorType(colorType);
            result.Compression = compressionMethod == 0 ? "Deflate (метод 0, единственный в спецификации PNG)" : $"Неизвестный метод ({compressionMethod})";
            result.ExtraInfo = $"{ColorTypeName(colorType)}; {(interlaceMethod == 1 ? "чересстрочная (Adam7)" : "без чересстрочности")}";

            for (int guard = 0; guard < 64; guard++) 
            {
                byte[] chunkHeader;
                try
                {
                    chunkHeader = ByteReader.ReadExact(stream, 8, "заголовок чанка");
                }
                catch (CorruptedFileException)
                {
                    break; 
                }

                uint len = ByteReader.ReadUInt32BE(chunkHeader, 0);
                string type = Encoding.ASCII.GetString(chunkHeader, 4, 4);

                if (type == "IDAT" || type == "IEND")
                    break;

                if (type == "pHYs" && len >= 9)
                {
                    byte[] phys = ByteReader.ReadExact(stream, 9, "данные чанка pHYs");
                    int ppuX = ByteReader.ReadInt32BE(phys, 0);
                    int ppuY = ByteReader.ReadInt32BE(phys, 4);
                    byte unit = phys[8];
                    if (unit == 1) // 1 = метры
                    {
                        result.DpiX = Math.Round(ppuX * 0.0254, 1);
                        result.DpiY = Math.Round(ppuY * 0.0254, 1);
                    }
                    stream.Seek(len - 9 + 4, SeekOrigin.Current); 
                }
                else
                {
                    stream.Seek(len + 4, SeekOrigin.Current); 
                }
            }

            if (fileSizeBytes >= 12)
            {
                stream.Seek(-12, SeekOrigin.End);
                byte[] tail = ByteReader.ReadExact(stream, 12, "хвост файла (проверка IEND)");
                string tailType = Encoding.ASCII.GetString(tail, 4, 4);
                if (tailType != "IEND")
                {
                    result.IsCorrupted = true;
                    result.ErrorMessage = "Отсутствует завершающий чанк IEND в конце файла.";
                }
            }
            else
            {
                result.IsCorrupted = true;
                result.ErrorMessage = "Файл слишком короткий для корректного PNG.";
            }

            return result;
        }

        private static int ChannelsForColorType(byte colorType)
        {
            switch (colorType)
            {
                case 0: return 1; 
                case 2: return 3; 
                case 3: return 1; 
                case 4: return 2; 
                case 6: return 4; 
                default: return 1;
            }
        }

        private static string ColorTypeName(byte colorType)
        {
            switch (colorType)
            {
                case 0: return "Оттенки серого";
                case 2: return "RGB (Truecolor)";
                case 3: return "Индексированный (палитра)";
                case 4: return "Оттенки серого + альфа";
                case 6: return "RGBA (Truecolor + альфа)";
                default: return $"Неизвестный тип цвета ({colorType})";
            }
        }
    }
}
