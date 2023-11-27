#pragma once

#include <random>

class Random
{
public:
    static void Init()
    {
        s_RandomEngine.seed(std::random_device()());
    }

    static float Float(float min, float max)
    {
        static std::uniform_real_distribution<> distrib(min, max);
        return distrib(s_RandomEngine);
    }

    static int Int(int min, int max)
    {
        static std::uniform_int_distribution<> distrib(min, max);
        return distrib(s_RandomEngine);
    }
    
private:
    static std::random_device rd;
    static std::mt19937 s_RandomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};