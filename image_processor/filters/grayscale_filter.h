#pragma once
#include "../utils/abstract_filter.h"

const double R_COEF = 0.299;
const double G_COEF = 0.587;
const double B_COEF = 0.114;

class GrayscaleFilter : public AbstractFilter {
public:
    void Process(Image& image) override;

private:
    double r_coef_ = R_COEF;
    double g_coef_ = G_COEF;
    double b_coef_ = B_COEF;
};