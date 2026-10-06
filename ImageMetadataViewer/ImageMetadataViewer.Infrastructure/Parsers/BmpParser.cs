using System;
using System.IO;

namespace ImageMetadataViewer.Infrastructure.Parsers
{

    public class BmpParser : IImageParser
    {
        public string FormatName => "BMP";

        public bool MatchesSignature(byte[] headerPeek)
        {
            return headerPeek.Length >= 2 && headerPeek[0] == 'B' && headerPeek[1] == 'M';
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


            byte[] header = ByteReader.ReadExact(stream, 14, "BITMAPFILEHEADER");

            uint bfSize = ByteReader.ReadUInt32LE(header, 2); 

            if (bfSize > 0 && fileSizeBytes < bfSize)
            {
                result.IsCorrupted = true;
                result.ErrorMessage = $"В заголовке заявлен размер {bfSize} байт, а реальный размер файла — {fileSizeBytes} байт.";
                return result;
            }

            byte[] infoSizeBuf = ByteReader.ReadExact(stream, 4, "biSize (размер info-заголовка)");
            uint biSize = ByteReader.ReadUInt32LE(infoSizeBuf, 0);

            if (biSize == 12)
            {
                byte[] core = ByteReader.ReadExact(stream, 8, "BITMAPCOREHEADER");
                result.WidthPx = ByteReader.ReadUInt16LE(core, 0);
                result.HeightPx = ByteReader.ReadUInt16LE(core, 2);
                result.ColorDepthBits = ByteReader.ReadUInt16LE(core, 6); 
                result.Compression = "Без сжатия (BITMAPCOREHEADER не хранит сжатие)";
                result.ExtraInfo = "Старый формат заголовка (OS/2 BITMAPCOREHEADER)";
                return result;
            }

            byte[] info = ByteReader.ReadExact(stream, 36, "BITMAPINFOHEADER");

            int width = ByteReader.ReadInt32LE(info, 0);
            int height = ByteReader.ReadInt32LE(info, 4);
            ushort bitCount = ByteReader.ReadUInt16LE(info, 10);
            uint compression = ByteReader.ReadUInt32LE(info, 12);
            int xPelsPerMeter = ByteReader.ReadInt32LE(info, 20);
            int yPelsPerMeter = ByteReader.ReadInt32LE(info, 24);

            result.WidthPx = width;
            result.HeightPx = Math.Abs(height); 
            result.ColorDepthBits = bitCount;
            result.Compression = CompressionName(compression);

            if (xPelsPerMeter > 0) result.DpiX = Math.Round(xPelsPerMeter * 0.0254, 1);
            if (yPelsPerMeter > 0) result.DpiY = Math.Round(yPelsPerMeter * 0.0254, 1);

            if (height < 0)
                result.ExtraInfo = "Строки сверху вниз (top-down), height отрицательный в заголовке";

            return result;
        }

        private static string CompressionName(uint code)
        {
            switch (code)
            {
                case 0: return "BI_RGB (без сжатия)";
                case 1: return "BI_RLE8";
                case 2: return "BI_RLE4";
                case 3: return "BI_BITFIELDS";
                case 4: return "BI_JPEG";
                case 5: return "BI_PNG";
                case 6: return "BI_ALPHABITFIELDS";
                default: return $"Неизвестный код сжатия ({code})";
            }
        }
    }
}
