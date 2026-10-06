using System.IO;

namespace ImageMetadataViewer.Infrastructure.Parsers
{

    public class PcxParser : IImageParser
    {
        public string FormatName => "PCX";

        public bool MatchesSignature(byte[] headerPeek)
        {
            return headerPeek.Length >= 1 && headerPeek[0] == 0x0A;
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

            byte[] h = ByteReader.ReadExact(stream, 128, "заголовок PCX (128 байт)");

            byte manufacturer = h[0];
            byte encoding = h[2];
            byte bitsPerPixel = h[3];
            ushort xMin = ByteReader.ReadUInt16LE(h, 4);
            ushort yMin = ByteReader.ReadUInt16LE(h, 6);
            ushort xMax = ByteReader.ReadUInt16LE(h, 8);
            ushort yMax = ByteReader.ReadUInt16LE(h, 10);
            ushort hDpi = ByteReader.ReadUInt16LE(h, 12);
            ushort vDpi = ByteReader.ReadUInt16LE(h, 14);
            byte nPlanes = h[65];

            if (manufacturer != 0x0A)
            {
                result.IsCorrupted = true;
                result.ErrorMessage = "Неверная сигнатура PCX (байт Manufacturer должен быть 0x0A).";
                return result;
            }

            result.WidthPx = xMax - xMin + 1;
            result.HeightPx = yMax - yMin + 1;
            result.ColorDepthBits = bitsPerPixel * nPlanes;
            result.Compression = encoding == 1 ? "RLE (packbits-подобное построчное сжатие)" : $"Без сжатия (код {encoding})";

            if (hDpi > 0) result.DpiX = hDpi;
            if (vDpi > 0) result.DpiY = vDpi;

            result.ExtraInfo = $"{nPlanes} цветовых плоскостей × {bitsPerPixel} бит";

            return result;
        }
    }
}
