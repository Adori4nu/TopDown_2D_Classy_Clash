#pragma once
#include "raylib.h"

class Character
{
public:
    Character(int window_width, int window_height)
    {
        width = static_cast<float>(texture.width) / max_frame;
        height = static_cast<float>(texture.height);
        screen_position = {
        static_cast<float>(window_width) * 0.5f - sprite_scale * (0.5f * width),
        static_cast<float>(window_height) * 0.5f - sprite_scale * (0.5f * height)
        };
    };

    void tick(float delta_time);
    void UndoMovement() { world_position = world_position_last_frame; };
    Vector2 GetWorldPosition() const { return world_position; };
    ~Character() 
    {
        UnloadTexture(texture); 
        UnloadTexture(idle_texture);
        UnloadTexture(runing_texture);    
    };
private:
    Texture2D texture{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D idle_texture{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D runing_texture{LoadTexture("textures/characters/knight_run_spritesheet.png")};
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