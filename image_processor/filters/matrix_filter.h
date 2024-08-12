#pragma once
#include "../utils/abstract_filter.h"

class MatrixFilter : public AbstractFilter {
public:
    explicit MatrixFilter(int** matrix);
    ~MatrixFilter() override;
    void Process(Image& image) override;

private:
    double** matrix_float_;

protected:
    int NearestCoord(int coord, int max_coord);
    void CorrectColor(double& color);
};