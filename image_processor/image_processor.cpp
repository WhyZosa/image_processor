#include "utils/file_worker.h"
#include "utils/image.h"
#include "utils/image_handler.h"
#include "filters/my_own_filter.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        ImageHandler image_handler;

        image_handler.HandleInput(argc, argv);
        image_handler.Process();
        image_handler.SaveImage();
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}