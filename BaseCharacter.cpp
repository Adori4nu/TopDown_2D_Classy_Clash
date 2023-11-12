#include "BaseCharacter.hpp"
#include "include/raymath.h"

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

    if (Vector2Length(velocity) != 0)
    {
        // Set world_position = world_position + velocity
        world_position = Vector2Add(world_position, Vector2Scale(Vector2Normalize(velocity), _speed));
        velocity.x < 0.f ? right_left = -1.f : right_left = 1.f;
        _texture = _runing_texture;
    }
    else
    {
        _texture = _idle_texture;
    }
    velocity = {};

    Rectangle source{frame * width, 0.f, right_left * width, height};
    Rectangle dest{GetScreenPosition().x, GetScreenPosition().y, sprite_scale * width, sprite_scale * height};
    DrawTexturePro(_texture, source, dest, Vector2{}, 0.f, WHITE);
};

int BaseCharacter::TakeDamage(int damage)
{
    _health -= damage;
    if (_health <= 0.f)
    {
        SetIsAlive(false);
        return 1;
    }
    return 0;
}