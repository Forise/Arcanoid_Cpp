#pragma once
#include <math.h>
#include <cctype>
#include <random>



static class Utils
{
public:
	static float dotProduct(float v1[2], const float v2[2]) {
        float product = 0;
        for (int i = 0; i < 2; i++)
            product += v1[i] * v2[i];
        return product;
    }

    static float* normalize(float* v)
    {
        float v0pow = *(v + 0) * *(v + 0);
        float v1pow = *(v + 1) * *(v + 1);
        float mag = sqrt(v0pow + v1pow);

        if (mag < 0)
        {
            mag = mag * -1;
        }

        v[0] /= mag;
        v[1] /= mag;
        return v;
    }

    using u32 = uint_least32_t;
    using engine = std::mt19937;

    static int getRandom(int min, int max)
    {
        std::random_device os_seed;
        const u32 seed = os_seed();
        engine generator(seed);
        std::uniform_int_distribution< u32 > distribute(min, max);
        return distribute(generator);
    }
};

