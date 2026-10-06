namespace ImageMetadataViewer.Infrastructure
{

    public class ImageMetadata
    {
        public string FileName { get; set; }
        public string FilePath { get; set; }
        public long FileSizeBytes { get; set; }

        public string Format { get; set; } = "Неизвестно";

        public int? WidthPx { get; set; }
        public int? HeightPx { get; set; }

        public double? DpiX { get; set; }
        public double? DpiY { get; set; }

        public int? ColorDepthBits { get; set; }

        public string Compression { get; set; }

        public string ExtraInfo { get; set; }

        public bool IsCorrupted { get; set; }
        public string ErrorMessage { get; set; }
    }
}
