using System;
using System.IO;

namespace ImageMetadataViewer.Infrastructure.Parsers
{
   
    public class TiffParser : IImageParser
    {
        public string FormatName => "TIFF";

        public bool MatchesSignature(byte[] headerPeek)
        {
            if (headerPeek.Length < 4) return false;
            bool little = headerPeek[0] == 'I' && headerPeek[1] == 'I';
            bool big = headerPeek[0] == 'M' && headerPeek[1] == 'M';
            if (!little && !big) return false;

            ushort version = little
                ? (ushort)(headerPeek[2] | (headerPeek[3] << 8))
                : (ushort)((headerPeek[2] << 8) | headerPeek[3]);
            return version == 42;
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

            byte[] head = ByteReader.ReadExact(stream, 8, "заголовок TIFF");
            bool little = head[0] == 'I';

            uint ifdOffset = little ? ByteReader.ReadUInt32LE(head, 4) : ByteReader.ReadUInt32BE(head, 4);
            if (ifdOffset + 2 > fileSizeBytes)
            {
                result.IsCorrupted = true;
                result.ErrorMessage = "Смещение на IFD указывает за пределы файла.";
                return result;
            }

            stream.Seek(ifdOffset, SeekOrigin.Begin);
            byte[] countBuf = ByteReader.ReadExact(stream, 2, "число записей IFD");
            ushort entryCount = little ? ByteReader.ReadUInt16LE(countBuf, 0) : ByteReader.ReadUInt16BE(countBuf, 0);

            if (entryCount == 0 || entryCount > 4096) 
            {
                result.IsCorrupted = true;
                result.ErrorMessage = $"Подозрительное число записей IFD: {entryCount}.";
                return result;
            }

            int? width = null, height = null, bitsPerSample = null, samplesPerPixel = null;
            uint? compressionTag = null, resolutionUnit = null;
            double? xRes = null, yRes = null;

            for (int i = 0; i < entryCount; i++)
            {
                byte[] entry = ByteReader.ReadExact(stream, 12, $"запись IFD #{i}");
                ushort tag = little ? ByteReader.ReadUInt16LE(entry, 0) : ByteReader.ReadUInt16BE(entry, 0);
                ushort type = little ? ByteReader.ReadUInt16LE(entry, 2) : ByteReader.ReadUInt16BE(entry, 2);
                uint count = little ? ByteReader.ReadUInt32LE(entry, 4) : ByteReader.ReadUInt32BE(entry, 4);

                switch (tag)
                {
                    case 256: width = (int)ReadTiffValueAsUInt(entry, 8, type, little); break;
                    case 257: height = (int)ReadTiffValueAsUInt(entry, 8, type, little); break;
                    case 258: bitsPerSample = (int)ReadFirstOfArrayOrInline(stream, entry, type, count, little); break;
                    case 259: compressionTag = ReadTiffValueAsUInt(entry, 8, type, little); break;
                    case 277: samplesPerPixel = (int)ReadTiffValueAsUInt(entry, 8, type, little); break;
                    case 282: xRes = ReadRational(stream, entry, type, little); break;
                    case 283: yRes = ReadRational(stream, entry, type, little); break;
                    case 296: resolutionUnit = ReadTiffValueAsUInt(entry, 8, type, little); break;
                }
            }

            result.WidthPx = width;
            result.HeightPx = height;

            int channels = samplesPerPixel ?? 1;
            result.ColorDepthBits = bitsPerSample.HasValue ? bitsPerSample.Value * channels : (int?)null;
            result.Compression = CompressionName(compressionTag);


            if (xRes.HasValue && resolutionUnit == 2) result.DpiX = Math.Round(xRes.Value, 1);
            else if (xRes.HasValue && resolutionUnit == 3) result.DpiX = Math.Round(xRes.Value * 2.54, 1);

            if (yRes.HasValue && resolutionUnit == 2) result.DpiY = Math.Round(yRes.Value, 1);
            else if (yRes.HasValue && resolutionUnit == 3) result.DpiY = Math.Round(yRes.Value * 2.54, 1);

            result.ExtraInfo = $"Порядок байт: {(little ? "little-endian (II)" : "big-endian (MM)")}; каналов: {channels}";

            return result;
        }

        private static uint ReadTiffValueAsUInt(byte[] entry, int valueOffset, ushort type, bool little)
        {
            if (type == 3) 
                return little ? ByteReader.ReadUInt16LE(entry, valueOffset) : ByteReader.ReadUInt16BE(entry, valueOffset);
            return little ? ByteReader.ReadUInt32LE(entry, valueOffset) : ByteReader.ReadUInt32BE(entry, valueOffset);
        }

        private static uint ReadFirstOfArrayOrInline(Stream stream, byte[] entry, ushort type, uint count, bool little)
        {
            int elementSize = type == 3 ? 2 : 4; 
            int totalSize = elementSize * (int)count;

            if (totalSize <= 4)
                return ReadTiffValueAsUInt(entry, 8, type, little);

            uint offset = little ? ByteReader.ReadUInt32LE(entry, 8) : ByteReader.ReadUInt32BE(entry, 8);
            long savedPos = stream.Position;
            stream.Seek(offset, SeekOrigin.Begin);
            byte[] first = ByteReader.ReadExact(stream, elementSize, "первый элемент массива BitsPerSample");
            stream.Seek(savedPos, SeekOrigin.Begin);

            return type == 3
                ? (little ? ByteReader.ReadUInt16LE(first, 0) : ByteReader.ReadUInt16BE(first, 0))
                : (little ? ByteReader.ReadUInt32LE(first, 0) : ByteReader.ReadUInt32BE(first, 0));
        }

        private static double? ReadRational(Stream stream, byte[] entry, ushort type, bool little)
        {
            if (type != 5) return null;

            uint offset = little ? ByteReader.ReadUInt32LE(entry, 8) : ByteReader.ReadUInt32BE(entry, 8);
            long savedPos = stream.Position;
            stream.Seek(offset, SeekOrigin.Begin);
            byte[] rational = ByteReader.ReadExact(stream, 8, "значение RATIONAL");
            stream.Seek(savedPos, SeekOrigin.Begin);

            uint numerator = little ? ByteReader.ReadUInt32LE(rational, 0) : ByteReader.ReadUInt32BE(rational, 0);
            uint denominator = little ? ByteReader.ReadUInt32LE(rational, 4) : ByteReader.ReadUInt32BE(rational, 4);

            return denominator == 0 ? (double?)null : (double)numerator / denominator;
        }

        private static string CompressionName(uint? code)
        {
            if (!code.HasValue) return "Не указано";
            switch (code.Value)
            {
                case 1: return "Без сжатия";
                case 2: return "CCITT Group 3 (1D)";
                case 5: return "LZW";
                case 6: return "Старый JPEG (deprecated)";
                case 7: return "JPEG";
                case 8: return "Deflate (Adobe)";
                case 32773: return "PackBits";
                default: return $"Код {code.Value}";
            }
        }
    }
}
