#include "Enemy.hpp"
#include "Character.hpp"

#include <raymath.h>

Enemy::Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale)
{
    _texture = idle_texture;
    _idle_texture = idle_texture;
    _runing_texture = run_texture;
    world_position = position;
    sprite_scale = scale;
    width = static_cast<float>(_texture.width) / max_frame;
    height = static_cast<float>(_texture.height);
    speed = 2.5f;
}

void Enemy::tick(float delta_time)
{
    if (_target == nullptr)
    {
        return;
    }
    Vector2 to_target = Vector2Normalize(Vector2Subtract(_target->GetScreenPosition(), screen_position));

    world_position = Vector2Add(world_position, Vector2Scale(to_target, speed));

    screen_position = Vector2Subtract(world_position, _target->GetWorldPosition());

    BaseCharacter::tick(delta_time);
}

