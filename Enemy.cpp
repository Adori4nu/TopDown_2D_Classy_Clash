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
}

void Enemy::tick(float delta_time)
{
    screen_position = Vector2Subtract(world_position, _target->GetWorldPosition());

    BaseCharacter::tick(delta_time);
}
