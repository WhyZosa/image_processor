#include "file_worker.h"

void FileWorker::ReadImage(Image& image, const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        // обработка исключения (не удалось открыть файл)
        throw std::invalid_argument("Failed to open a file");
    }

    file.read(reinterpret_cast<char*>(&image.bmp_header), sizeof(image.bmp_header));
    file.read(reinterpret_cast<char*>(&image.dib_header), sizeof(image.dib_header));

    if (image.bmp_header.signature[0] != 'B' || image.bmp_header.signature[1] != 'M') {
        // обработка исключения (файл другого формата)
        throw std::invalid_argument("Invalid BMP file");
    }

    if (image.dib_header.bitsPerPixel != PIXEL_FORMAT) {
        // обработка исключения (не тот формат пикселя)
        throw std::invalid_argument("Unsoppurted pixel format. Only 24-bit bitmap is supported");
    }

    int32_t width = image.dib_header.width;
    int32_t height = image.dib_header.height;

    image.pixels.assign(height, std::vector<Pixel>(width));

    int padding = (4 - static_cast<int>(width * sizeof(Pixel) % 4)) % 4;

    // потому что в BMP картинка перевернута
    for (int32_t row = height - 1; row >= 0; row--) {
        file.read(reinterpret_cast<char*>(image.pixels[row].data()), static_cast<int64_t>(width * sizeof(Pixel)));
        file.seekg(padding, std::ios::cur);
    }

    file.close();
}

void FileWorker::HeadersUpdating(Image& image) {
    // Вычисление нового размера файла
    int padding = (4 - static_cast<int>(image.Width() * sizeof(Pixel)) % 4) % 4;
    int data_size = static_cast<int>(image.Width() * image.Height() * sizeof(Pixel));
    uint64_t file_size = sizeof(BMPheader) + sizeof(DIBheader) + data_size + padding * image.Height();

    image.bmp_header.fileSize = static_cast<uint32_t>(file_size);

    // Изменение размера изображения
    image.dib_header.width = static_cast<int32_t>(image.Width());
    image.dib_header.height = static_cast<int32_t>(image.Height());
}

void FileWorker::WriteImage(Image& image, const std::string& path) {
    if (path.size() < 4 || path.substr(path.size() - 4, 4) != ".bmp") {
        throw std::invalid_argument("Wrong output file format");
    }

    std::ofstream file(path, std::ios::binary);
    if (!file) {
        // обработка исключения (ошибка открытия)
        throw std::invalid_argument("Failed to open output file");
    }

    HeadersUpdating(image);

    file.write(reinterpret_cast<char*>(&image.bmp_header), sizeof(image.bmp_header));
    file.write(reinterpret_cast<char*>(&image.dib_header), sizeof(image.dib_header));

    int padding = (4 - static_cast<int>(image.Width() * sizeof(Pixel)) % 4) % 4;

    for (int32_t row = static_cast<int32_t>(image.Height()) - 1; row >= 0; row--) {

        file.write(reinterpret_cast<char*>(image.pixels[row].data()),
                   static_cast<std::streamsize>(image.Width() * sizeof(Pixel)));
        file.seekp(padding, std::ios::cur);
    }

    file.close();
}