#pragma once
#include "image.h"

struct FloatPixel {
    double blue;
    double green;
    double red;
};

class AbstractFilter {
public:
    virtual void Process(Image& image) = 0;
    virtual ~AbstractFilter() {
    }
};