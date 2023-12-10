#include "World.hpp"

void World::LoadMap()
{
    for (size_t i = 0; i < std::size(tile_map); ++i)
    {
        tile_map[i] = 41;
    }
}
