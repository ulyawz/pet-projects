# Color Model Converter

A desktop application for converting colors between **RGB, XYZ, and HSV** color models.

The application provides an interactive interface where changing values in one color model automatically recalculates the corresponding values in the other models.

## Features

- RGB ↔ XYZ conversion
- RGB ↔ HSV conversion
- Automatic recalculation of color values
- Interactive color component sliders
- Manual numerical input
- System color picker
- Support for different illuminants:
  - D65
  - D50
  - E
- Automatic calculation of the transformation matrix
- RGB gamut checking
- Clipping of RGB values outside the valid range
- Visual color preview
- Automated tests for mathematical conversions

## Color Models

### RGB

The RGB model represents a color using three components:

- Red
- Green
- Blue

### XYZ

The XYZ color space is used as an intermediate color model for colorimetric transformations.

### HSV

HSV represents colors using:

- Hue
- Saturation
- Value

## Architecture

The application follows the **Model–View–ViewModel (MVVM)** approach.

```text
ColorModelConverter
├── ColorModelConverter.App
│   ├── View
│   └── ViewModel
│
├── ColorModelConverter.Core
│   ├── ColorModel
│   ├── ColorMath
│   ├── MatrixMath
│   ├── Illuminant
│   └── RgbPrimaries
│
└── ColorModelConverter.Tests