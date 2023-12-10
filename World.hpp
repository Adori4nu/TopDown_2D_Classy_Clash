#pragma once

#include "include/raylib.h"

#include <array>
#include <list>
#include <span>
#include <string>

constexpr float ASSET_SCALE{4.0f};

class GameObject;

class World
{
public:
    World(Texture2D world_texture) : _world_texture(world_texture) { LoadMap(); };

    __forceinline Texture2D GetWorldTexture() const { return _world_texture; };
    __forceinline Vector2 GetMapPosition() const { return map_positon; };
    __forceinline void SetMapPos(Vector2 map_pos) { map_positon = map_pos; };

    void LoadMap();

    Rectangle tile_source{0, 0, 32, 32};
    Rectangle tile_destination{0, 0, tile_source.width * ASSET_SCALE, tile_source.height * ASSET_SCALE };
    std::string map_file_path{};
    std::array<int/*Tile*/, 24*24> tile_map{};
    std::span<int> tile_map_view;
    int map_width{24};
    int map_height{24};
protected:
    Texture2D _world_texture;
    Vector2 map_positon{0.f ,0.f};
private:
};

class Tile
{
    friend class World;
public:
    Tile(/*World* world, Vector2 world_pos*/)
        /*: _world(world)
        , world_position(world_pos)*/
        {};

protected:

private:
    // World* _world;
    // Vector2 world_position{};
    Rectangle tile_content{};
    bool can_not_enter{false};
    // std::list<GameObject> cel_occupants;
};