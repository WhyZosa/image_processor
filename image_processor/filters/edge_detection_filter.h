#pragma once
#include "../utils/abstract_filter.h"
#include "grayscale_filter.h"
#include "matrix_filter.h"

const int CENTER_EDGE_DETECTION = 4;
const int SIDES_EDGE_DETECTION = -1;

class EdgeDetectionFilter : public GrayscaleFilter, public MatrixFilter {
public:
    explicit EdgeDetectionFilter(double threshold);
    ~EdgeDetectionFilter() override;
    void Process(Image& image) override;

private:
    double threshold_;
    int** CreateFilter();
    int** filter_;
};