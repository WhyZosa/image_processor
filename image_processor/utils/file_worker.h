#pragma once
#include "image.h"
#include <string>
#include <stdexcept>

const int PIXEL_FORMAT = 24;

class FileWorker {
public:
    void ReadImage(Image& image, const std::string& path);
    void HeadersUpdating(Image& image);
    void WriteImage(Image& image, const std::string& path);
};