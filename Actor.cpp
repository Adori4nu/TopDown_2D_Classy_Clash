#include "Actor.hpp"

#include "include/raymath.h"

void Actor::tick(float delta_time)
{
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
};