add_executable(
    image_processor
    filters/crop_filter.cpp
    filters/edge_detection_filter.cpp
    utils/file_worker.cpp
    filters/gaussian_blur_filter.cpp
    filters/grayscale_filter.cpp
    utils/image_handler.cpp
    utils/image.cpp
    filters/matrix_filter.cpp
    filters/my_own_filter.cpp
    filters/negative_filter.cpp
    filters/perlin_noise.cpp
    filters/sharpening_filter.cpp
    image_processor.cpp
)
target_include_directories(image_processor PRIVATE .)