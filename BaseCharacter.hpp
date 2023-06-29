#pragma once
#include <raylib.h>

class BaseCharacter
{
public:
    virtual void tick(float delta_time);
    void UndoMovement() { world_position = world_position_last_frame; };
    Vector2 GetWorldPosition() const { return world_position; };
    virtual Vector2 GetScreenPosition() const = 0;
    Rectangle GetCollisionRectangle() const
    {
        return Rectangle {
            GetScreenPosition().x,
            GetScreenPosition().y,
            sprite_scale * width,
            sprite_scale * height
        };
    }
protected:
    Texture2D _texture{};
    Texture2D _idle_texture{};
    Texture2D _runing_texture{};
    Vector2 world_position{};
    Vector2 world_position_last_frame{};
    Vector2 velocity{};
    float right_left{1.f};
    float running_time{};
    int frame{};
    int max_frame{6};
    float frame_update_time{1.f / 12.f};
    float speed{4.f};
    float sprite_scale{4.f};
    float width{};
    float height{};
};