#include "Pawn.hpp"

#include "include/raymath.h"

void Pawn::tick(float delta_time)
{
    world_position_last_frame = GetWorldPosition();

    Actor::tick(delta_time);

    if (Vector2Length(velocity) != 0)
    {
        // Set world_position = world_position + velocity
        SetWorldPosition(Vector2Add(world_position, Vector2Scale(Vector2Normalize(velocity), _speed)));
        velocity.x < 0.f ? right_left = -1.f : right_left = 1.f;
        _texture = _runing_texture;
    }
    else
    {
        _texture = _idle_texture;
    }
    velocity = {};
}
