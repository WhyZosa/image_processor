#pragma once
#include "matrix_filter.h"

const int CENTER_SHARPENING = 5;
const int SIDES_SHARPENING = -1;

class SharpeningFilter : public MatrixFilter {
public:
    SharpeningFilter();
    ~SharpeningFilter() override;
    void Process(Image& image) override;

private:
    int** CreateFilter();
    int** filter_;
};