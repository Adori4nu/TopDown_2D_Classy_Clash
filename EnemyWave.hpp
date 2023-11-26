#pragma once
#include "include/raylib.h"

#include <array>

class BaseEnemy;

class EnemyWave
{
public:
    EnemyWave();

private:
    std::array<std::array<BaseEnemy, 64>, 3> EnemyWaves;
};