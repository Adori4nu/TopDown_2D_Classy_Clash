#pragma once
#include <string>

struct AttackInformations
{
    std::string name{};

    int min_damage{};
    int max_damage{};

    float range{};
};

struct DefenseInformations
{
    int min_defense{};
    int max_defense{};
};