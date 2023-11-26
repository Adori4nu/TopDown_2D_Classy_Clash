#pragma once

#include "include/raylib.h"

class World
{
public:
    World(Texture2D world_texture) : _world_texture(world_texture) {};

    __forceinline Texture2D GetWorldTexture() const { return _world_texture; };
    __forceinline Vector2 GetMapPosition() const { return map_positon; };
    __forceinline void SetMapPos(Vector2 map_pos) { map_positon = map_pos; };
protected:
    Texture2D _world_texture;
    Vector2 map_positon{0.f ,0.f};
private:
};