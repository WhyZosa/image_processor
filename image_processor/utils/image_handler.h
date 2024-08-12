#pragma once
#include "image.h"
#include "file_worker.h"
#include "../filters/filters_include.h"

class ImageHandler {
public:
    void HandleInput(int argc, char** argv);
    ~ImageHandler();
    void Process();
    void SaveImage();

private:
    Image image_;
    FileWorker file_worker_;
    std::string write_path_;
    std::vector<AbstractFilter*> filters_;
};