#pragma once
#include "include/raylib.h"

#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include "helperFunctions.hpp"

class Prop : public GameObject
{
public:
    Prop(ObjectType type
        , const Vector2& world_position
        , int texture
        , float sprite_scale)
        : GameObject(type, world_position)
        , sprite_scale(sprite_scale)
        { 
            sprite_info.idle_texture_id_ = texture;
            sprite_info.max_frame = 1;
            const auto& texture_ = GetTexture(sprite_info.idle_texture_id_);
            width = static_cast<float>(texture_.width) / sprite_info.max_frame;
            height = static_cast<float>(texture_.height);
        };

    Rectangle GetCollisionRectangle() const
    {
        return Rectangle {
            world_position.x,
            world_position.y,
            width * sprite_scale,
            height * sprite_scale
        };
    }
    // __forceinline Texture2D GetTexture() const { return texture; };
    __forceinline float GetSpriteScale() const { return sprite_scale; };
    __forceinline GraphicsComponent GetSpriteComponent() const { return sprite_info; };

    __forceinline void SetWidthAndHeight()
    {
        const auto& texture = GetTexture(sprite_info.idle_texture_id_);
        width = static_cast<float>(texture.width) / sprite_info.max_frame;
        height = static_cast<float>(texture.height); 
    };
private:
    GraphicsComponent sprite_info{};
    float sprite_scale{4.f};
    float width{};
    float height{};
};