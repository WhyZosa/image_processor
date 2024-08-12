#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#pragma pack(push, 1)

struct BMPheader {
    char signature[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct DIBheader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

#pragma pack(pop)

struct Image {
    std::vector<std::vector<Pixel> > pixels;
    BMPheader bmp_header;
    DIBheader dib_header;

    size_t Height() const;
    size_t Width() const;
};