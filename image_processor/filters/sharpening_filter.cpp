#include "sharpening_filter.h"

SharpeningFilter::~SharpeningFilter() {
    for (int i = 0; i < 3; i++) {
        delete[] filter_[i];
    }
    delete[] filter_;
}

int** SharpeningFilter::CreateFilter() {
    filter_ = new int*[3];
    for (int i = 0; i < 3; i++) {
        filter_[i] = new int[3];
    }

    filter_[0][0] = 0;
    filter_[0][1] = SIDES_SHARPENING;
    filter_[0][2] = 0;
    filter_[1][0] = SIDES_SHARPENING;
    filter_[1][1] = CENTER_SHARPENING;
    filter_[1][2] = SIDES_SHARPENING;
    filter_[2][0] = 0;
    filter_[2][1] = SIDES_SHARPENING;
    filter_[2][2] = 0;

    return filter_;
}

SharpeningFilter::SharpeningFilter() : MatrixFilter(CreateFilter()) {
}

void SharpeningFilter::Process(Image& image) {
    MatrixFilter::Process(image);
    std::vector<std::vector<FloatPixel>> pixel_floats(image.Height(), std::vector<FloatPixel>(image.Width()));

    // Применяем матрицу фильтра напрямую, без конвертации в uint8_t
    for (int x = 0; x < image.Height(); x++) {
        for (int y = 0; y < image.Width(); y++) {
            double blue = 0.0;
            double green = 0.0;
            double red = 0.0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = NearestCoord(x + dx, static_cast<int>(image.Height()));
                    int ny = NearestCoord(y + dy, static_cast<int>(image.Width()));

                    double filter_value = filter_[dx + 1][dy + 1];
                    blue +=
                        filter_value * static_cast<double>(image.pixels[nx][ny].blue) / static_cast<double>(UINT8_MAX);
                    green +=
                        filter_value * static_cast<double>(image.pixels[nx][ny].green) / static_cast<double>(UINT8_MAX);
                    red +=
                        filter_value * static_cast<double>(image.pixels[nx][ny].red) / static_cast<double>(UINT8_MAX);
                }
            }

            // Корректировка и сохранение результатов
            CorrectColor(blue);
            CorrectColor(green);
            CorrectColor(red);
            pixel_floats[x][y].blue = blue;
            pixel_floats[x][y].green = green;
            pixel_floats[x][y].red = red;
        }
    }
}