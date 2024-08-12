#include "image.h"

size_t Image::Height() const {
    return pixels.size();
}

size_t Image::Width() const {
    if (Height() == 0) {
        return 0;
    }

    return pixels[0].size();
}