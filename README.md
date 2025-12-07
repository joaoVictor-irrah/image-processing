# Image Processing

A C++ project being made to study image processing fundamentals and modern C++ practices. This project demonstrates loading, manipulating, and writing image files in various formats.

## Overview

This project is being made to study both **C++** and **Image Processing** concepts. It provides a simple yet extensible framework for reading and writing images, manipulating pixel data, and understanding how image formats are handled at a low level.

## Features

- 📁 **Multi-format Support**: Load and save images in PNG, JPG, BMP, and TGA formats
- 🎨 **Pixel Manipulation**: Direct access to image data for pixel-level operations
- 📦 **Object-Oriented Design**: Clean Image class abstraction for image data
- 🔧 **Copy Semantics**: Support for copying and transforming image data
- 📐 **Image Creation**: Generate images from scratch with specified dimensions and channels

## Project Structure

```
image-processing/
├── src/
│   ├── Image.h              # Image class definition
│   ├── Image.cpp            # Image class implementation
│   ├── main.cpp             # Example usage and demonstrations
│   ├── stb_image.h          # STB image loading library
│   └── stb_image_write.h    # STB image writing library
├── CMakeLists.txt           # Build configuration
└── README.md                # This file
```

## Building the Project

### Prerequisites

- C++14 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.0 or higher

### Build Instructions

```bash
# Create a build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the application
./image_processing
```

## Usage

### Basic Example

```cpp
#include "Image.h"

int main() {
    // Load an image
    Image test("input.png");
    
    // Copy the image
    Image copy = test;
    
    // Manipulate pixel data (set all pixels to white)
    for (int i = 0; i < copy.w * copy.channels; ++i) {
        copy.data[i] = 255;
    }
    
    // Write to a new file
    copy.write("output.png");
    
    // Create a blank image (100x100, RGB)
    Image blank(100, 100, 3);
    blank.write("blank.jpg");
    
    return 0;
}
```

## Libraries Used

- **[stb_image](https://github.com/nothings/stb)** - Single-file image loading library
- **[stb_image_write](https://github.com/nothings/stb)** - Single-file image writing library

## License

This project is open source and available for educational purposes.

## Author

[JoaoVictor-irrah](https://github.com/joaoVictor-irrah)\
[JoaoMadeiraxyz](https://github.com/joaomadeiraxyz)
