#pragma once
#include "include/raylib.h"
#include "include/raymath.h"

#include "GameObject.hpp"


class Actor : public GameObject
{
public:
    Actor(ObjectType type
        , Texture2D idle_texture
        , Vector2 world_pos
        , float scale
        ) 
        : GameObject(type, world_pos)
        , _idle_texture(idle_texture)
        , sprite_scale(scale)
        { 
            _texture = _idle_texture;
            width = static_cast<float>(_texture.width) / max_frame;
            height = static_cast<float>(_texture.height);
        };
    Actor(ObjectType type
        , Texture2D idle_texture
        , float scale
        ) 
        : GameObject(type)
        , _idle_texture(idle_texture)
        , sprite_scale(scale)
        { 
            _texture = _idle_texture;
            width = static_cast<float>(_texture.width) / max_frame;
            height = static_cast<float>(_texture.height);
        };
    virtual void tick(float delta_time);
    
    __forceinline Texture2D GetTexture() const { return _texture; };
    
    virtual Vector2 GetScreenPosition(Vector2 player_position) const { return Vector2Subtract(world_position, player_position); };
    virtual Rectangle GetCollisionRectangle(Vector2 player_position) const
    {
        Vector2 screen_position {Vector2Subtract(world_position, player_position)};
        return Rectangle {
            screen_position.x,
            screen_position.y,
            static_cast<float>(_texture.width) * sprite_scale,
            static_cast<float>(_texture.height) * sprite_scale
        };
    }
    __forceinline float GetRightLeftDirection() const { return right_left; };
    __forceinline int GetFrame() const { return frame; };
    __forceinline int GetMaxFrame() const { return max_frame; };
    __forceinline float GetFrameUpdateTime() const { return frame_update_time; };
    __forceinline float GetSpriteScale() const { return sprite_scale; };
    __forceinline float GetWidth() const { return width; };
    __forceinline float GetHeight() const { return height; };

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
    Texture2D _texture{};
    Texture2D _idle_texture{};
    
    float right_left{1.f};
    float running_time{};
    int frame{};
    int max_frame{6};
    float frame_update_time{1.f / 12.f};
    float sprite_scale{4.f};
    float width{};
    float height{};
    
    // GraphicsEngine _graphicsComponent;
private:
};