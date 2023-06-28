#pragma once
#include <raylib.h>

class Enemy
{                           
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale);
    void tick(float delta_time);
    void UndoMovement() { world_position = world_position_last_frame; };
    Vector2 GetWorldPosition() const { return world_position; };
    Rectangle GetCollisionRectangle() const;
private:
    Texture2D texture;
    Texture2D idle_texture;
    Texture2D runing_texture;
    Vector2 screen_position{};
    Vector2 world_position{};
    Vector2 world_position_last_frame{};
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