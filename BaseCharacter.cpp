#include "BaseCharacter.hpp"

void BaseCharacter::tick(float delta_time)
{
    world_position_last_frame = world_position;
    
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
    DrawTexturePro(_texture, source, dest, Vector2{}, 0.f, WHITE);
};