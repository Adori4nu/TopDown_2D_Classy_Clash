#pragma once
#include "include/raylib.h"
#include "EnemyWave.hpp"

#include <vector>

class BaseEnemy;
class EnemyType;

class EnemySpawner
{
public:
    EnemySpawner() {};
    void tick(float delta_time);
    void AddWave(EnemyWave wave_data);

private:
    std::vector<EnemyWave> wave_spawns_data;

};