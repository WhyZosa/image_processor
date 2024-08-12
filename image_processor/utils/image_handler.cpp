#include "image_handler.h"
#include "cstring"

ImageHandler::~ImageHandler() {
    for (size_t i = 0; i < filters_.size(); i++) {
        delete filters_[i];
    }
    filters_.clear();
}

void ImageHandler::HandleInput(int argc, char** argv) {
    if (argc == 1) {
        throw std::invalid_argument("There is no arguments");
    } else if (argc == 2) {
        throw std::invalid_argument("There is no output path");
    }

    try {
        file_worker_.ReadImage(image_, argv[1]);
    } catch (const std::invalid_argument& e) {
        throw e;
    }

    write_path_ = argv[2];

    int i = 3;

    while (i < argc) {
        if (strcmp(argv[i], "-crop") == 0) {
            int height = 0;
            int width = 0;

            if (i + 2 >= argc) {
                throw std::invalid_argument("Not enough arguments");
            }

            try {
                height = std::stoi(argv[i + 1]);
                width = std::stoi(argv[i + 2]);
            } catch (...) {
                throw std::invalid_argument("Invalid -crop arguments");
            }

            filters_.push_back(new CropFilter(height, width));
            i += 3;
        } else if (strcmp(argv[i], "-gs") == 0) {
            filters_.push_back(new GrayscaleFilter());
            i++;
        } else if (strcmp(argv[i], "-neg") == 0) {
            filters_.push_back(new NegativeFilter());
            i++;
        } else if (strcmp(argv[i], "-sharp") == 0) {
            filters_.push_back(new SharpeningFilter());
            i++;
        } else if (strcmp(argv[i], "-edge") == 0) {
            double threshold = 0;

            if (i + 1 >= argc) {
                throw std::invalid_argument("Not enough arguments");
            }

            try {
                threshold = std::stod(argv[i + 1]);
            } catch (...) {
                throw std::invalid_argument("Invalid -edge argument");
            }

            if (threshold < 0) {
                threshold = 0;
            }

            filters_.push_back(static_cast<MatrixFilter*>(new EdgeDetectionFilter(threshold)));
            i += 2;
        } else if (strcmp(argv[i], "-blur") == 0) {
            double sigma = 0.0;

            if (i + 1 >= argc) {
                throw std::invalid_argument("Not enough arguments");
            }

            try {
                sigma = std::stod(argv[i + 1]);
            } catch (...) {
                throw std::invalid_argument("Invalid -sigma argument");
            }

            if (sigma < 0) {
                throw std::invalid_argument("Invalid -sigma argument");
            }

            filters_.push_back(new GaussianBlurFilter(sigma));
            i += 2;
        } else if (strcmp(argv[i], "-xor") == 0) {
            int octaves = 0;

            if (i + 1 >= argc) {
                throw std::invalid_argument("Not enough arguments");
            }

            try {
                octaves = std::stoi(argv[i + 1]);
            } catch (...) {
                throw std::invalid_argument("Invalid -xor argument");
            }

            if (octaves < 0) {
                throw std::invalid_argument("Invalid -xor argument");
            }

            filters_.push_back(new MyOwnClass(octaves));
            i += 2;
        } else {
            throw std::invalid_argument(std::string("Non-existent filter: ") + std::string(argv[i]));
        }
    }
}

void ImageHandler::Process() {
    for (auto filter : filters_) {
        filter->Process(image_);
    }
}

void ImageHandler::SaveImage() {
    try {
        file_worker_.WriteImage(image_, write_path_);
    } catch (std::invalid_argument& e) {
        throw e;
    }
}