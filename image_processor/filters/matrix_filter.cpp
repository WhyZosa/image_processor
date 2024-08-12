#include "matrix_filter.h"
#include <cmath>

MatrixFilter::MatrixFilter(int** matrix) {
    matrix_float_ = new double*[3];
    for (size_t i = 0; i < 3; i++) {
        matrix_float_[i] = new double[3];
    }

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            matrix_float_[i][j] = static_cast<double>(matrix[i][j]) / UINT8_MAX;
        }
    }
}

MatrixFilter::~MatrixFilter() {
    for (size_t i = 0; i < 3; i++) {
        delete[] matrix_float_[i];
    }
    delete[] matrix_float_;
}

void MatrixFilter::CorrectColor(double& color) {
    color = std::min(1.0, std::max(0.0, color));
}

int MatrixFilter::NearestCoord(int coord, int max_coord) {
    if (coord < 0) {
        return 0;
    } else if (coord >= max_coord) {
        return max_coord - 1;
    } else {
        return coord;
    }
}

void MatrixFilter::Process(Image& image) {
    std::vector<std::vector<FloatPixel>> pixel_floats(image.Height(), std::vector<FloatPixel>(image.Width()));

    int delta[]{-1, 0, -1};

    for (int x = 0; x < image.Height(); x++) {
        for (int y = 0; y < image.Width(); y++) {
            for (auto dx : delta) {
                for (auto dy : delta) {
                    int x_1 = NearestCoord(x + dx, static_cast<int>(image.Height()));
                    int y_1 = NearestCoord(y + dy, static_cast<int>(image.Width()));

                    pixel_floats[x][y].blue += matrix_float_[dx + 1][dy + 1] * image.pixels[x_1][y_1].blue;
                    pixel_floats[x][y].green += matrix_float_[dx + 1][dy + 1] * image.pixels[x_1][y_1].green;
                    pixel_floats[x][y].red += matrix_float_[dx + 1][dy + 1] * image.pixels[x_1][y_1].red;
                }
            }

            CorrectColor(pixel_floats[x][y].blue);
            CorrectColor(pixel_floats[x][y].green);
            CorrectColor(pixel_floats[x][y].red);
        }
    }

    for (size_t x = 0; x < image.Height(); x++) {
        for (size_t y = 0; y < image.Width(); y++) {
            image.pixels[x][y].blue = static_cast<uint8_t>(std::round(pixel_floats[x][y].blue * UINT8_MAX));
            image.pixels[x][y].green = static_cast<uint8_t>(std::round(pixel_floats[x][y].green * UINT8_MAX));
            image.pixels[x][y].red = static_cast<uint8_t>(std::round(pixel_floats[x][y].red * UINT8_MAX));
        }
    }
}