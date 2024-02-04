#pragma once
#include "include/raylib.h"
#include "include/raymath.h"

#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include "helperFunctions.hpp"


class Actor : public GameObject
{
public:
    Actor(ObjectType type
        , int idle_texture
        , Vector2 world_pos
        , float scale
        ) 
        : GameObject(type, world_pos)
        , sprite_scale(scale)
        {
            sprite_info.idle_texture_id_ = idle_texture;
            const auto& texture = GetTexture(sprite_info.idle_texture_id_);
            width = static_cast<float>(texture.width) / sprite_info.max_frame;
            height = static_cast<float>(texture.height);
        };
    Actor(ObjectType type
        , int idle_texture
        , float scale
        ) 
        : GameObject(type)
        , sprite_scale(scale)
        {
            sprite_info.idle_texture_id_ = idle_texture;
            const auto& texture = GetTexture(sprite_info.idle_texture_id_);
            // _texture = _idle_texture;
            width = static_cast<float>(texture.width) / sprite_info.max_frame;
            height = static_cast<float>(texture.height);
        };
    virtual void tick(float delta_time);
    
    // __forceinline Texture2D GetTexture() const { return _texture; };
    
    virtual Vector2 GetScreenPosition(Vector2 player_position) const { return Vector2Subtract(world_position, player_position); };
    virtual Rectangle GetCollisionRectangle(Vector2 player_position) const
    {
        return Rectangle {
            world_position.x,
            world_position.y,
            static_cast<float>(width) * sprite_scale,
            static_cast<float>(height) * sprite_scale
        };
    }
    __forceinline float GetRightLeftDirection() const { return right_left; };
    __forceinline int GetFrame() const { return sprite_info.frame; };
    
    __forceinline float GetFrameUpdateTime() const { return frame_update_time; };
    __forceinline float GetSpriteScale() const { return sprite_scale; };
    __forceinline float GetWidth() const { return width; };
    __forceinline float GetHeight() const { return height; };

    __forceinline GraphicsComponent GetSpriteComponent() const { return sprite_info; };
    
    __forceinline void SetWidthAndHeight()
    {
        const auto& texture = GetTexture(sprite_info.idle_texture_id_);
        width = static_cast<float>(texture.width) / sprite_info.max_frame;
        height = static_cast<float>(texture.height); 
    };

    friend std::ostream& operator<<(std::ostream& os, const Actor& character) {
        os << static_cast<const GameObject&>(character);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Actor& character) {
        is >> static_cast<GameObject&>(character);
        return is;
    }

protected:
    // Render
    GraphicsComponent sprite_info{};
    
    float right_left{1.f};
    float running_time{};
    float frame_update_time{1.f / 12.f};
    float sprite_scale{4.f};
    float width{};
    float height{};

private:
};