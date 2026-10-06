
### `ImageMetadataViewer/README.md`


# Image Metadata Viewer

A desktop application developed in **C#** and **WPF** for analyzing image files and displaying their metadata.

The application can process images from selected folders and extract key information about their structure and properties.

## Features

- Select a folder containing images
- Scan image files
- Display image metadata
- Show file name
- Show image dimensions
- Show resolution
- Show color depth
- Show compression information
- Support for multiple image formats
- Progress reporting during folder scanning

## Supported Formats

The project contains parsers for:

- JPEG
- PNG
- BMP
- GIF
- PCX
- TIFF

## Architecture

The application is divided into several independent components:

```text
ImageMetadataViewer
├── ImageMetadataViewer.App
│   └── WPF user interface
│
├── ImageMetadataViewer.Engine
│   └── Folder scanning and processing
│
└── ImageMetadataViewer.Infrastructure
    ├── Image metadata models
    ├── Byte reading
    └── Image format parsers