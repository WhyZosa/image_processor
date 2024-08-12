#include "negative_filter.h"

void NegativeFilter::Process(Image& image) {
    for (int x = 0; x < image.Height(); x++) {
        for (int y = 0; y < image.Width(); y++) {
            image.pixels[x][y].blue = UINT8_MAX - image.pixels[x][y].blue;
            image.pixels[x][y].green = UINT8_MAX - image.pixels[x][y].green;
            image.pixels[x][y].red = UINT8_MAX - image.pixels[x][y].red;
        }
    }
}