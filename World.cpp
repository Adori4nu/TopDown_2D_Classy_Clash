#include "World.hpp"

#include "GameObject.hpp"

void World::Add(GameObject *game_object)
{
    Vector2 object_world_pos = game_object->GetWorldPosition();
    int x = object_world_pos.x / tile_destination.width;
    int y = object_world_pos.y / tile_destination.height;
    int tile_index = y * 24 + x; // 24 - world width
    tile_map.at(tile_index).cel_occupants.push_back(game_object);
}

void World::LoadMap()
{
    for (size_t i = 0; i < std::size(tile_map); ++i)
    {
        tile_map[i].tile_content_id = 41;
    }
}

void World::ClearWorld()
{
	// CurrentMap.ObjectLayers.clear();
	// CurrentMap.TileLayers.clear();
	// ClearSprites();
    
	// Effects.clear();
}

void World::ClearTiles()
{
    // tile_map.fill();
}