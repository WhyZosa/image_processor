#include "gaussian_blur_filter.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(double sigma_a) : sigma_(sigma_a) {
    kernel_size_ = static_cast<int>(GAUSS_RADIUS * sigma_ + 1);
    // должно быть нечетным
    if (kernel_size_ % 2 == 0) {
        kernel_size_++;
    }
}

int GaussianBlurFilter::NearestCoord(int coord, int max_coord) {
    if (coord < 0) {
        return 0;
    } else if (coord >= max_coord) {
        return max_coord - 1;
    } else {
        return coord;
    }
}

void GaussianBlurFilter::Process(Image& image) {

    int width = static_cast<int>(image.Width());
    int height = static_cast<int>(image.Height());

    std::vector<std::vector<FloatPixel>> blurred_pixels_by_y(height, std::vector<FloatPixel>(width));
    std::vector<std::vector<FloatPixel>> blurred_pixels_by_x(height, std::vector<FloatPixel>(width));

    // Создаем ядро Гаусса
    std::vector<double> kernel(kernel_size_);
    double sum = 0.0;

    for (int x = -kernel_size_ / 2; x <= kernel_size_ / 2; ++x) {
        double exponent = -(x * x) / (2 * sigma_ * sigma_);
        double weight = exp(exponent) / (2 * M_PI * sigma_ * sigma_);
        kernel[x + kernel_size_ / 2] = weight;
        sum += weight;
    }

    for (int i = 0; i < kernel_size_; ++i) {
        kernel[i] /= sum;
    }

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            double red_sum = 0.0;
            double green_sum = 0.0;
            double blue_sum = 0.0;
            for (int i = -kernel_size_ / 2; i <= kernel_size_ / 2; ++i) {
                int new_y = y + i;
                new_y = NearestCoord(new_y, width);
                red_sum += kernel[i + kernel_size_ / 2] * image.pixels[x][new_y].red / UINT8_MAX;
                green_sum += kernel[i + kernel_size_ / 2] * image.pixels[x][new_y].green / UINT8_MAX;
                blue_sum += kernel[i + kernel_size_ / 2] * image.pixels[x][new_y].blue / UINT8_MAX;
            }
            blurred_pixels_by_y[x][y].red = red_sum;
            blurred_pixels_by_y[x][y].green = green_sum;
            blurred_pixels_by_y[x][y].blue = blue_sum;
        }
    }

    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < height; ++x) {
            double red_sum = 0.0;
            double green_sum = 0.0;
            double blue_sum = 0.0;
            for (int i = -kernel_size_ / 2; i <= kernel_size_ / 2; ++i) {
                int new_x = x + i;
                new_x = NearestCoord(new_x, height);
                red_sum += kernel[i + kernel_size_ / 2] * blurred_pixels_by_y[new_x][y].red;
                green_sum += kernel[i + kernel_size_ / 2] * blurred_pixels_by_y[new_x][y].green;
                blue_sum += kernel[i + kernel_size_ / 2] * blurred_pixels_by_y[new_x][y].blue;
            }
            blurred_pixels_by_x[x][y].red = red_sum;
            blurred_pixels_by_x[x][y].green = green_sum;
            blurred_pixels_by_x[x][y].blue = blue_sum;
        }
    }

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            image.pixels[x][y].red = static_cast<uint8_t>(blurred_pixels_by_x[x][y].red * UINT8_MAX);
            image.pixels[x][y].green = static_cast<uint8_t>(blurred_pixels_by_x[x][y].green * UINT8_MAX);
            image.pixels[x][y].blue = static_cast<uint8_t>(blurred_pixels_by_x[x][y].blue * UINT8_MAX);
        }
    }
}