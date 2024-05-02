#pragma once

#include <random>

class Random
{
public:
    static void init()
    {
        srand(time(nullptr));
    }

    static int get_int(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }
};
