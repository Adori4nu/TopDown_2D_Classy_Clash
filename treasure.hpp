#pragma once
#include "include/raylib.h"

#include "Item.hpp"

#include <vector>

struct TreasureInstance
{
    int item_id{ -1 };
    int quantity{ 1 };

    Vector2 position{ 0,0 };
    int texture_id{};
};

std::vector<TreasureInstance> GetLoot(const std::string& loot_name);