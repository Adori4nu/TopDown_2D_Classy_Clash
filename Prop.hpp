#pragma once
#include "include/raylib.h"

#include "GameObject.hpp"
class Prop : public GameObject
{
public:
    Prop(ObjectType type
        , const Vector2& world_position
        , Texture2D& texture
        , float sprite_scale)
        : GameObject(type, world_position)
        , texture(texture), sprite_scale(sprite_scale)
        {};

    Rectangle GetCollisionRectangle() const
    {
        return Rectangle {
            world_position.x,
            world_position.y,
            static_cast<float>(texture.width) * sprite_scale,
            static_cast<float>(texture.height) * sprite_scale
        };
    }
    __forceinline Texture2D GetTexture() const { return texture; };
    __forceinline float GetSpriteScale() const { return sprite_scale; };
private:
    Texture2D texture{};
    float sprite_scale{4.f};
};