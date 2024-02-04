#include "Actor.hpp"

#include "include/raymath.h"

void Actor::tick(float delta_time)
{
    running_time += delta_time;
    if (running_time >= frame_update_time)
    {
        sprite_info.frame++;
        running_time = 0.f;
        if (sprite_info.frame > sprite_info.max_frame)
        {
            sprite_info.frame = 0;
        }
    }
};