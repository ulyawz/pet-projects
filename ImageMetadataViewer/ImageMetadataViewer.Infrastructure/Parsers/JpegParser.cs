using System;
using System.IO;
using System.Text;

namespace ImageMetadataViewer.Infrastructure.Parsers
{
  
    public class JpegParser : IImageParser
    {
        public string FormatName => "JPEG";

        public bool MatchesSignature(byte[] headerPeek)
        {
            return headerPeek.Length >= 2 && headerPeek[0] == 0xFF && headerPeek[1] == 0xD8;
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

            stream.Seek(2, SeekOrigin.Begin); 

            bool sofFound = false;

            for (int guard = 0; guard < 500 && !sofFound; guard++) 
            {
                byte[] markerBuf;
                try { markerBuf = ByteReader.ReadExact(stream, 2, "маркер сегмента"); }
                catch (CorruptedFileException) { break; }

                if (markerBuf[0] != 0xFF)
                    break; 

                byte marker = markerBuf[1];

                if (marker == 0xD8 || marker == 0x01 || (marker >= 0xD0 && marker <= 0xD7))
                    continue;
                if (marker == 0xD9) 
                    break;

                byte[] lenBuf;
                try { lenBuf = ByteReader.ReadExact(stream, 2, "длина сегмента"); }
                catch (CorruptedFileException) { break; }
                int segmentLen = ByteReader.ReadUInt16BE(lenBuf, 0);
                if (segmentLen < 2) break;

                bool isSofMarker = marker >= 0xC0 && marker <= 0xCF
                                    && marker != 0xC4 && marker != 0xC8 && marker != 0xCC;

                if (isSofMarker)
                {
                    byte[] sof = ByteReader.ReadExact(stream, segmentLen - 2, "данные SOF");
                    byte precision = sof[0];
                    int height = ByteReader.ReadUInt16BE(sof, 1);
                    int width = ByteReader.ReadUInt16BE(sof, 3);
                    byte numComponents = sof[5];

                    result.WidthPx = width;
                    result.HeightPx = height;
                    result.ColorDepthBits = precision * numComponents;
                    result.Compression = SofName(marker);
                    sofFound = true;
                }
                else if (marker == 0xE0) 
                {
                    byte[] app0 = ByteReader.ReadExact(stream, segmentLen - 2, "данные APP0");
                    if (app0.Length >= 12 && Encoding.ASCII.GetString(app0, 0, 5) == "JFIF\0")
                    {
                        byte units = app0[7];
                        int xDensity = ByteReader.ReadUInt16BE(app0, 8);
                        int yDensity = ByteReader.ReadUInt16BE(app0, 10);

                        if (units == 1) 
                        {
                            result.DpiX = xDensity;
                            result.DpiY = yDensity;
                        }
                        else if (units == 2)
                        {
                            result.DpiX = Math.Round(xDensity * 2.54, 1);
                            result.DpiY = Math.Round(yDensity * 2.54, 1);
                        }
                       
                    }
                }
                else
                {
                    stream.Seek(segmentLen - 2, SeekOrigin.Current); 
                }
            }

            if (!sofFound)
            {
                result.IsCorrupted = true;
                result.ErrorMessage = "Не найден маркер SOF (структура JPEG повреждена или файл обрезан).";
            }

            if (fileSizeBytes >= 2)
            {
                stream.Seek(-2, SeekOrigin.End);
                byte[] tail = ByteReader.ReadExact(stream, 2, "хвост файла (проверка EOI)");
                if (!(tail[0] == 0xFF && tail[1] == 0xD9))
                {
                    result.IsCorrupted = true;
                    result.ErrorMessage = (result.ErrorMessage == null ? "" : result.ErrorMessage + " ")
                        + "Отсутствует маркер EOI (FF D9) в конце файла.";
                }
            }

            return result;
        }

        private static string SofName(byte marker)
        {
            switch (marker)
            {
                case 0xC0: return "JPEG Baseline (DCT)";
                case 0xC1: return "JPEG Extended sequential (DCT)";
                case 0xC2: return "JPEG Progressive (DCT)";
                case 0xC3: return "JPEG Lossless";
                default: return $"JPEG (SOF-маркер 0x{marker:X2})";
            }
        }
    }
}
