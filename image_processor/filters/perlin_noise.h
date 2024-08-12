#pragma once
#include "../utils/abstract_filter.h"

const int GRID_SIZE = 400;
const uint32_t HASH_1 = 3284157443;
const uint32_t HASH_2 = 1911520717;
const uint32_t HASH_3 = 2048419325;
const double INTERPOLATE_COEF_1 = 3;
const double INTERPOLATE_COEF_2 = 2;

struct Vector2 {
    double x;
    double y;
};

class PerlinNoise {
public:
    double Noise(double x, double y, int octaves);

private:
    double BasicNoise(double x, double y);
    Vector2 RandomGradient(int i_x, int i_y);
    double DotGridGradient(int i_x, int i_y, double x, double y);
    double Interpolate(double a, double b, double w);
};