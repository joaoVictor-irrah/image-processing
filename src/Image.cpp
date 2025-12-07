//
// Created by João Madeira on 06/12/25.
//

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <unistd.h>

Image::Image(const char* filename) : w(0), h(0), channels(0), size(0) {
    if (read(filename)) {
        printf("Read %s\n", filename);
        size = w*h*channels;
    } else {
        printf("Failed to read %s\n", filename);
    }
}
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w*h*channels;
    data = new uint8_t[size];
}
Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
    memcpy(data, img.data, size);
}
Image::~Image() {
    stbi_image_free(data);
}

bool Image::read (const char* filename) {
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != nullptr;
}
bool Image::write(const char* filename) const {
    const ImageType type = getFileType(filename);
    int success = 0;
    switch (type) {
        case PNG: {
            stbi_write_png_compression_level = 9;
            success = stbi_write_png(filename, w, h, channels, data, w*channels);
            
            // Post-process with ffmpeg to further optimize PNG compression
            if (success) {
                // Convert a relative path to an absolute path for ffmpeg
                char abs_filename[PATH_MAX];
                if (filename[0] == '/') {
                    snprintf(abs_filename, sizeof(abs_filename), "%s", filename);
                } else {
                    char cwd[PATH_MAX];
                    getcwd(cwd, sizeof(cwd));
                    snprintf(abs_filename, sizeof(abs_filename), "%s/%s", cwd, filename);
                }
                
                char tempfile[PATH_MAX];
                snprintf(tempfile, sizeof(tempfile), "%s.tmp.png", abs_filename);
                
                // Command to optimize PNG with ffmpeg using absolute paths
                char cmd[2048];
                snprintf(cmd, sizeof(cmd), 
                    R"(bash -c '/opt/homebrew/bin/ffmpeg -i "%s" -c:v png -compression_level 9 -frames:v 1 -update 1 "%s" -y 2>/dev/null')",
                    abs_filename, tempfile);

                system(cmd);

                FILE* tmpcheck = fopen(tempfile, "rb");
                if (tmpcheck != nullptr) {
                    fclose(tmpcheck);
                    // Move optimized file back to original
                    snprintf(cmd, sizeof(cmd), "mv '%s' '%s'", tempfile, abs_filename);
                    system(cmd);
                }
            }
            break;
        }
        case JPG:
            success = stbi_write_jpg(filename, w, h, channels, data, 95);
            break;
        case BMP:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case TGA:
            success = stbi_write_tga(filename, w, h, channels, data);
    }
    return success != 0;
}
ImageType Image::getFileType(const char *filename) {
    const char* ext = strrchr(filename, '.');
    if (ext != nullptr) {
        if (strcmp(ext, ".png") == 0) return PNG;
        if (strcmp(ext, ".jpg") == 0) return JPG;
        if (strcmp(ext, ".bmp") == 0) return BMP;
        if (strcmp(ext, ".tga") == 0) return TGA;
    }
    return PNG;
}
