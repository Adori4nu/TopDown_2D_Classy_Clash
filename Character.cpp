#include "Character.hpp"
#include "raymath.h"

void Character::tick(float delta_time)
{
    world_position_last_frame = world_position;
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
    {
        direction.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D))
    {
        direction.x += 1.0f;
    }
    if (IsKeyDown(KEY_W))
    {
        direction.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y += 1.0f;
    }
    if (Vector2Length(direction) != 0)
    {
        // Set world_position = world_position + direction
        world_position = Vector2Add(world_position, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = runing_texture;
    }
    else
    {
        texture = idle_texture;
    }
    running_time += delta_time;
    if (running_time >= frame_update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame > max_frame)
        {
            frame = 0;
        }
    }

    Rectangle source{frame * width, 0.f, right_left * width, height};
    Rectangle dest{screen_position.x, screen_position.y, sprite_scale * width, sprite_scale * height};
    DrawTexturePro(texture, source, dest, Vector2{sprite_scale * width * 0.5f, sprite_scale * height * 0.5f}, 0.f, WHITE);
}