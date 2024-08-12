/*вообщем таки проблема была такая trehsold был в uint а надо в double
  есть 2 решения проблемы, переписывать все включая фильтры и так далее
  или делать как я и искать ленивое решение*/

#include "edge_detection_filter.h"

EdgeDetectionFilter::~EdgeDetectionFilter() {
    for (size_t i = 0; i < 3; i++) {
        delete[] filter_[i];
    }
    delete[] filter_;
}

int** EdgeDetectionFilter::CreateFilter() {
    filter_ = new int*[3];
    for (size_t i = 0; i < 3; i++) {
        filter_[i] = new int[3];
    }

    filter_[0][0] = 0;
    filter_[0][1] = SIDES_EDGE_DETECTION;
    filter_[0][2] = 0;
    filter_[1][0] = SIDES_EDGE_DETECTION;
    filter_[1][1] = CENTER_EDGE_DETECTION;
    filter_[1][2] = SIDES_EDGE_DETECTION;
    filter_[2][0] = 0;
    filter_[2][1] = SIDES_EDGE_DETECTION;
    filter_[2][2] = 0;

    return filter_;
}

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : MatrixFilter(CreateFilter()), threshold_(threshold) {
}

void EdgeDetectionFilter::Process(Image& image) {
    GrayscaleFilter::Process(image);

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

    for (size_t x = 0; x < image.Height(); x++) {
        for (size_t y = 0; y < image.Width(); y++) {
            if (pixel_floats[x][y].red >= threshold_) {
                image.pixels[x][y].red = UINT8_MAX;
                image.pixels[x][y].green = UINT8_MAX;
                image.pixels[x][y].blue = UINT8_MAX;
            } else {
                image.pixels[x][y].red = 0;
                image.pixels[x][y].green = 0;
                image.pixels[x][y].blue = 0;
            }
        }
    }
}