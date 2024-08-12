#include "crop_filter.h"

CropFilter::CropFilter(size_t width, size_t height) : height_new_(height), width_new_(width) {
}

void CropFilter::Process(Image& image) {
    // создаем новые значения, потому что фильтр может использоваться несколько раз
    size_t height_new = height_new_;
    size_t width_new = width_new_;

    if (height_new > image.Height()) {
        height_new = image.Height();
    }
    if (width_new > image.Width()) {
        width_new = image.Width();
    }

    image.pixels.resize(height_new);
    for (int i = 0; i < image.Height(); i++) {
        image.pixels[i].resize(width_new);
    }
}