#include "my_own_filter.h"
#include "perlin_noise.h"

MyOwnClass::MyOwnClass(int octaves) : octaves_(octaves) {
}

void MyOwnClass::Process(Image& image) {
    PerlinNoise perlin;

    for (size_t x = 0; x < image.Height(); x++) {
        for (size_t y = 0; y < image.Width(); y++) {
            double x_1 = static_cast<double>(x);
            double y_1 = static_cast<double>(y);

            uint8_t color = static_cast<uint8_t>(perlin.Noise(x_1, y_1, octaves_) * UINT8_MAX);

            image.pixels[x][y].red ^= color;
            image.pixels[x][y].green ^= color;
            image.pixels[x][y].blue ^= color;
        }
    }
}