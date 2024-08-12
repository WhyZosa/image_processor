#pragma once
#include "../utils/abstract_filter.h"

class NegativeFilter : public AbstractFilter {
public:
    void Process(Image& image) override;
};