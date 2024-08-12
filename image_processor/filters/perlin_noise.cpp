#include "perlin_noise.h"
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>

Vector2 PerlinNoise::RandomGradient(int i_x, int i_y) {
    const uint32_t w = 8 * sizeof(uint32_t);
    const uint32_t s = w / 2;
    uint32_t a = static_cast<uint32_t>(i_x);
    uint32_t b = static_cast<uint32_t>(i_y);
    a *= HASH_1;

    b ^= a << s | a >> (w - s);
    b *= HASH_2;

    a ^= b << s | b >> (w - s);
    a *= HASH_3;
    double random = a * (M_PI / ~(~0u >> 1));  // [0, 2*Pi]

    // Создаем вектор из углов
    Vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

double PerlinNoise::DotGridGradient(int i_x, int i_y, double x, double y) {
    Vector2 gradient = RandomGradient(i_x, i_y);

    double dx = x - static_cast<double>(i_x);
    double dy = y - static_cast<double>(i_y);

    return (dx * gradient.x + dy * gradient.y);
}

double PerlinNoise::Interpolate(double a, double b, double w) {
    return (b - a) * (INTERPOLATE_COEF_1 - w * INTERPOLATE_COEF_2) * w * w + a;
}

double PerlinNoise::BasicNoise(double x, double y) {
    int x_0 = static_cast<int>(x);
    int y_0 = static_cast<int>(y);
    int x_1 = x_0 + 1;
    int y_1 = y_0 + 1;

    // Считаем веса интерполяции
    double s_x = x - static_cast<double>(x_0);
    double s_y = y - static_cast<double>(y_0);

    // Интерполируем углы
    double n_0 = DotGridGradient(x_0, y_0, x, y);
    double n_1 = DotGridGradient(x_1, y_0, x, y);
    double i_x_0 = Interpolate(n_0, n_1, s_x);

    n_0 = DotGridGradient(x_0, y_1, x, y);
    n_1 = DotGridGradient(x_1, y_1, x, y);
    double i_x_1 = Interpolate(n_0, n_1, s_x);

    // Интерполируем всё вместе
    double value = Interpolate(i_x_0, i_x_1, s_y);

    return value;
}

double PerlinNoise::Noise(double x, double y, int octaves) {
    double val = 0;
    double freq = 1;
    double amp = 1;

    for (int i = 0; i < octaves; i++) {
        val += BasicNoise(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;

        freq *= 2;
        amp /= 2;
    }

    if (val > 1) {
        val = 1;
    } else if (val < -1) {
        val = -1;
    }

    return (val + 1) / 2;
}