#pragma once
#include "../utils/abstract_filter.h"

class MyOwnClass : public AbstractFilter {
public:
    explicit MyOwnClass(int octaves);
    void Process(Image& image) override;

private:
    int octaves_;
};