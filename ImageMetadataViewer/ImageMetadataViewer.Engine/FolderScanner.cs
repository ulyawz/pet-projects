using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using ImageMetadataViewer.Infrastructure;

namespace ImageMetadataViewer.Engine
{

    public class FolderScanner
    {
        private static readonly HashSet<string> SupportedExtensions = new HashSet<string>(StringComparer.OrdinalIgnoreCase)
        {
            ".bmp", ".png", ".gif", ".jpg", ".jpeg", ".tif", ".tiff", ".pcx"
        };

        private readonly ParserRegistry _registry = new ParserRegistry();


        private const int BatchSize = 25;

        public async Task<IReadOnlyList<ImageMetadata>> ScanAsync(
            string folderPath,
            IProgress<ScanProgress> progress,
            CancellationToken cancellationToken)
        {

            var files = Directory.EnumerateFiles(folderPath, "*.*", SearchOption.TopDirectoryOnly)
                .Where(f => SupportedExtensions.Contains(Path.GetExtension(f)))
                .ToList();

            int total = files.Count;
            var allResults = new ConcurrentBag<ImageMetadata>();
            var pendingBatch = new ConcurrentQueue<ImageMetadata>();
            int processed = 0;

            progress?.Report(new ScanProgress { ProcessedCount = 0, TotalCount = total, NewlyCompleted = Array.Empty<ImageMetadata>() });

            var options = new ParallelOptions
            {
                MaxDegreeOfParallelism = Math.Max(1, Environment.ProcessorCount),
                CancellationToken = cancellationToken
            };

            await Task.Run(() =>
            {
                try
                {
                    Parallel.ForEach(files, options, filePath =>
                    {

                        var metadata = _registry.ParseFile(filePath);

                        allResults.Add(metadata);
                        pendingBatch.Enqueue(metadata);

                        int done = Interlocked.Increment(ref processed);
                        if (done % BatchSize == 0 || done == total)
                        {
                            var batch = DrainQueue(pendingBatch);
                            progress?.Report(new ScanProgress { ProcessedCount = done, TotalCount = total, NewlyCompleted = batch });
                        }
                    });
                }
                catch (OperationCanceledException)
                {

                }
            }, cancellationToken);

            return allResults.ToList();
        }

        private static List<ImageMetadata> DrainQueue(ConcurrentQueue<ImageMetadata> queue)
        {
            var batch = new List<ImageMetadata>();
            while (queue.TryDequeue(out var item))
                batch.Add(item);
            return batch;
        }
    }
}
