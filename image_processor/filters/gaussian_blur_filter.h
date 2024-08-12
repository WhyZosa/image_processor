#pragma once
#include "../utils/abstract_filter.h"

const double GAUSS_RADIUS = 6.0;

class GaussianBlurFilter : public AbstractFilter {
public:
    explicit GaussianBlurFilter(double sigma_a);
    void Process(Image& image) override;

private:
    double sigma_;
    int kernel_size_;
    int NearestCoord(int coord, int max_coord);
};