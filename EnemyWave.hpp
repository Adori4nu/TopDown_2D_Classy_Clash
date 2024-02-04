#pragma once
#include "EnemyType.hpp"

#include "optional"

struct EnemyWave // "Spawn_Info"
{
    int starting_time{};
    int end_time{};
    EnemyType mob;
    int mob_count{};
    float mob_spawn_delay{};
    float spawn_wait_clock{};
};