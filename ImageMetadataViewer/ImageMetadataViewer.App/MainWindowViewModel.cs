using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using ImageMetadataViewer.Engine;
using ImageMetadataViewer.Infrastructure;

namespace ImageMetadataViewer.App
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
        private readonly FolderScanner _scanner = new FolderScanner();
        private CancellationTokenSource _cts;
        private readonly Stopwatch _stopwatch = new Stopwatch();

        public event PropertyChangedEventHandler PropertyChanged;

        public ObservableCollection<ImageMetadata> Results { get; } = new ObservableCollection<ImageMetadata>();

        private int _total;
        public int Total { get => _total; private set { _total = value; Raise(nameof(Total)); Raise(nameof(ProgressPercent)); } }

        private int _processed;
        public int Processed { get => _processed; private set { _processed = value; Raise(nameof(Processed)); Raise(nameof(ProgressPercent)); } }

        private int _corruptedCount;
        public int CorruptedCount { get => _corruptedCount; private set { _corruptedCount = value; Raise(nameof(CorruptedCount)); } }

        private bool _isScanning;
        public bool IsScanning { get => _isScanning; private set { _isScanning = value; Raise(nameof(IsScanning)); } }

        public double ProgressPercent => Total == 0 ? 0 : 100.0 * Processed / Total;

        private string _statusText = "Выберите папку с изображениями.";
        public string StatusText { get => _statusText; private set { _statusText = value; Raise(nameof(StatusText)); } }

        public async Task StartScanAsync(string folderPath)
        {
            Results.Clear();
            Total = 0;
            Processed = 0;
            CorruptedCount = 0;
            IsScanning = true;
            StatusText = "Сканирование...";
            _stopwatch.Restart();

            _cts = new CancellationTokenSource();

            var progress = new Progress<ScanProgress>(OnProgress);

            try
            {
                await _scanner.ScanAsync(folderPath, progress, _cts.Token);
                StatusText = _cts.IsCancellationRequested ? "Сканирование отменено." : "Готово.";
            }
            catch (OperationCanceledException)
            {
                StatusText = "Сканирование отменено.";
            }
            catch (Exception ex)
            {
                StatusText = $"Ошибка сканирования: {ex.Message}";
            }
            finally
            {
                _stopwatch.Stop();
                IsScanning = false;
            }
        }

        public void CancelScan()
        {
            _cts?.Cancel();
        }

        private void OnProgress(ScanProgress p)
        {
            Total = p.TotalCount;
            Processed = p.ProcessedCount;

            foreach (var item in p.NewlyCompleted)
            {
                Results.Add(item);
                if (item.IsCorrupted) CorruptedCount++;
            }

            StatusText = $"Обработано {Processed} из {Total} • Битых файлов: {CorruptedCount} • {_stopwatch.Elapsed:mm\\:ss}";
        }

        private void Raise(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
