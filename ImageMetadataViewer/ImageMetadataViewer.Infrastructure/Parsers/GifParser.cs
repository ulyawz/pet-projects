using System;
using System.IO;

namespace ImageMetadataViewer.Infrastructure.Parsers
{
    public class GifParser : IImageParser
    {
        public string FormatName => "GIF";

        public bool MatchesSignature(byte[] headerPeek)
        {
            if (headerPeek.Length < 6) return false;
            string sig = System.Text.Encoding.ASCII.GetString(headerPeek, 0, 6);
            return sig == "GIF87a" || sig == "GIF89a";
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

            byte[] header = ByteReader.ReadExact(stream, 13, "GIF Header + Logical Screen Descriptor");

            string version = System.Text.Encoding.ASCII.GetString(header, 0, 6);
            ushort width = ByteReader.ReadUInt16LE(header, 6);
            ushort height = ByteReader.ReadUInt16LE(header, 8);
            byte packed = header[10];

            bool hasGlobalColorTable = (packed & 0x80) != 0;
            int colorResolutionBits = ((packed >> 4) & 0x07) + 1;
            int globalTableSizeBits = (packed & 0x07) + 1; 
            int globalTableColors = 1 << globalTableSizeBits;

            result.WidthPx = width;
            result.HeightPx = height;
            result.ColorDepthBits = hasGlobalColorTable ? globalTableSizeBits : colorResolutionBits;
            result.Compression = "LZW (всегда, часть спецификации GIF)";
            result.ExtraInfo = hasGlobalColorTable
                ? $"Версия {version}; глобальная палитра: {globalTableColors} цветов"
                : $"Версия {version}; глобальной палитры нет (только локальные)";


            if (fileSizeBytes >= 1)
            {
                stream.Seek(-1, SeekOrigin.End);
                int lastByte = stream.ReadByte();
                if (lastByte != 0x3B)
                {
                    result.IsCorrupted = true;
                    result.ErrorMessage = "Отсутствует GIF-трейлер (0x3B) в конце файла.";
                }
            }

            return result;
        }
    }
}
