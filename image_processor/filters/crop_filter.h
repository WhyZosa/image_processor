#pragma once
#include "../utils/abstract_filter.h"

class CropFilter : public AbstractFilter {
public:
    CropFilter(size_t width, size_t height);
    void Process(Image& image) override;

private:
    size_t height_new_;
    size_t width_new_;
};