using System.IO;

namespace ImageMetadataViewer.Infrastructure
{

    public interface IImageParser
    {
        string FormatName { get; }


        bool MatchesSignature(byte[] headerPeek);


        ImageMetadata Parse(string filePath, long fileSizeBytes, Stream stream);
    }
}
