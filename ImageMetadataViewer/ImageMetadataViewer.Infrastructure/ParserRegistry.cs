using System;
using System.Collections.Generic;
using System.IO;
using ImageMetadataViewer.Infrastructure.Parsers;

namespace ImageMetadataViewer.Infrastructure
{

    public class ParserRegistry
    {
        private readonly List<IImageParser> _parsers = new List<IImageParser>
        {
            new BmpParser(),
            new PngParser(),
            new GifParser(),
            new JpegParser(),
            new TiffParser(),
            new PcxParser()
        };

        private const int SignaturePeekSize = 16;

        public ImageMetadata ParseFile(string filePath)
        {
            var fileInfo = new FileInfo(filePath);

            try
            {
                using var stream = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read, bufferSize: 4096, useAsync: false);

                byte[] peek = new byte[SignaturePeekSize];
                int peekRead = stream.Read(peek, 0, peek.Length);
                if (peekRead < peek.Length)
                    Array.Resize(ref peek, peekRead);

                IImageParser parser = null;
                foreach (var p in _parsers)
                {
                    if (p.MatchesSignature(peek))
                    {
                        parser = p;
                        break;
                    }
                }

                if (parser == null)
                {
                    return new ImageMetadata
                    {
                        FileName = fileInfo.Name,
                        FilePath = filePath,
                        FileSizeBytes = fileInfo.Length,
                        Format = "Неизвестно / не поддерживается",
                        IsCorrupted = false
                    };
                }

                stream.Seek(0, SeekOrigin.Begin);
                return parser.Parse(filePath, fileInfo.Length, stream);
            }
            catch (Exception ex)
            {
                return new ImageMetadata
                {
                    FileName = fileInfo.Name,
                    FilePath = filePath,
                    FileSizeBytes = SafeLength(fileInfo),
                    Format = "?",
                    IsCorrupted = true,
                    ErrorMessage = ex is CorruptedFileException ? ex.Message : $"Ошибка чтения: {ex.Message}"
                };
            }
        }

        private static long SafeLength(FileInfo fileInfo)
        {
            try { return fileInfo.Length; } catch { return 0; }
        }
    }
}
