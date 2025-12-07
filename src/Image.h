#pragma once
#include <cstdint>
#include <cstdio>

enum ImageType {
    PNG, JPG, BMP, TGA
};

struct Image {
    uint8_t* data{};
    int w, h;
    int channels;
    size_t size;

    explicit Image(const char* filename);
    Image(int w, int h, int channels);
    Image(const Image& img);
    ~Image();

    bool read (const char* filename);
    bool write(const char* filename) const;

    static ImageType getFileType(const char* filename);
};
