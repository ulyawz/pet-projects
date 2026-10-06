using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;
using ImageMetadataViewer.Infrastructure;
using WinForms = System.Windows.Forms;

namespace ImageMetadataViewer.App
{
    public partial class MainWindow : Window
    {
        private readonly MainWindowViewModel _viewModel = new MainWindowViewModel();

        public MainWindow()
        {
            InitializeComponent();

            ResultsGrid.ItemsSource = _viewModel.Results;
            _viewModel.PropertyChanged += (s, e) => RefreshProgressUi();
            RefreshProgressUi();
        }

        private void RefreshProgressUi()
        {
            ScanProgressBar.Value = _viewModel.ProgressPercent;
            StatusText.Text = _viewModel.StatusText;
            ChooseFolderButton.IsEnabled = !_viewModel.IsScanning;
            CancelButton.IsEnabled = _viewModel.IsScanning;
        }

        private async void ChooseFolderButton_Click(object sender, RoutedEventArgs e)
        {
            using var dialog = new WinForms.FolderBrowserDialog
            {
                Description = "Выберите папку с изображениями",
                UseDescriptionForTitle = true
            };

            if (dialog.ShowDialog() != WinForms.DialogResult.OK)
                return;

            FolderPathText.Text = dialog.SelectedPath;


            await _viewModel.StartScanAsync(dialog.SelectedPath);
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            _viewModel.CancelScan();
        }

        private void ResultsGrid_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            var selected = ResultsGrid.SelectedItem as ImageMetadata;
            if (selected == null)
            {
                PreviewImage.Source = null;
                PreviewInfoText.Text = "";
                PreviewErrorText.Text = "";
                return;
            }

            PreviewInfoText.Text =
                $"{selected.FileName}\n" +
                $"Формат: {selected.Format}\n" +
                $"Размер файла: {selected.FileSizeBytes:N0} байт\n" +
                (selected.WidthPx.HasValue ? $"Пиксели: {selected.WidthPx}×{selected.HeightPx}\n" : "") +
                (selected.ColorDepthBits.HasValue ? $"Глубина цвета: {selected.ColorDepthBits} бит\n" : "") +
                (string.IsNullOrEmpty(selected.Compression) ? "" : $"Сжатие: {selected.Compression}\n");

            PreviewErrorText.Text = selected.IsCorrupted ? $"Файл повреждён: {selected.ErrorMessage}" : "";

            if (selected.IsCorrupted)
            {
                PreviewImage.Source = null;
                return;
            }

            try
            {
                var bitmap = new BitmapImage();
                bitmap.BeginInit();
                bitmap.CacheOption = BitmapCacheOption.OnLoad; 
                bitmap.UriSource = new Uri(selected.FilePath, UriKind.Absolute);
                bitmap.DecodePixelWidth = 400; 
                bitmap.EndInit();
                PreviewImage.Source = bitmap;
            }
            catch (Exception ex)
            {
                PreviewImage.Source = null;
                PreviewErrorText.Text = $"Не удалось отрисовать превью: {ex.Message}";
            }
        }
    }
}
