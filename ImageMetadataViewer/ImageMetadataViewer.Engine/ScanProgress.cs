using System.Collections.Generic;
using ImageMetadataViewer.Infrastructure;

namespace ImageMetadataViewer.Engine
{

    public class ScanProgress
    {
        public int ProcessedCount { get; set; }
        public int TotalCount { get; set; }
        public IReadOnlyList<ImageMetadata> NewlyCompleted { get; set; }
    }
}
