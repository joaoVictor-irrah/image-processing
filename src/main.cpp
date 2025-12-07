//
// Created by João Madeira on 06/12/25.
//

#include "Image.h"
#include <unistd.h>
#include <libgen.h>
#include <cstring>
#include <climits>

int main() {
    // Get the project root directory from the location of this source file
    char filepath[] = __FILE__;
    char* dir = dirname(filepath);
    char* parent = dirname(dir);
    
    // Change working directory to the project root
    chdir(parent);

    // ----------- IMAGE COPY / BLANK TESTS ------------

    // const Image test("test.png");
    // (void) test.write("new.png");
    // Image copy = test;
    // for (int i =0; i < copy.w*copy.channels; ++i) {
    //     copy.data[i] = 255;
    // }
    // copy.write("copy.png");
    // Image blank(100, 100, 3);
    // blank.write("blank.jpg");

    // -------- GRAYSCALE TESTS ----------

    const Image test("test2.jpg");
    Image gray_img = test;
    gray_img.grayscale_avg();
    gray_img.grayscale_lum();

    return 0;
}
