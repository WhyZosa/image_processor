#include "grayscale_filter.h"
#include <cmath>

void GrayscaleFilter::Process(Image& image) {
    for (int x = 0; x < image.Height(); x++) {
        for (int y = 0; y < image.Width(); y++) {
            uint8_t color_new =
                static_cast<uint8_t>(std::round(r_coef_ * image.pixels[x][y].red + g_coef_ * image.pixels[x][y].green +
                                                b_coef_ * image.pixels[x][y].blue));
            image.pixels[x][y].red = color_new;
            image.pixels[x][y].green = color_new;
            image.pixels[x][y].blue = color_new;
        }
    }
}