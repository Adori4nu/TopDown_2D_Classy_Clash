#include "Character.hpp"
#include <raymath.h>

Character::Character(
    int window_width,
    int window_height,
    Texture2D idle_texture,
    Texture2D run_texture,
    Vector2 position,
    float scale
    ) : _window_width(window_width), _window_height(window_height)
{
    _texture = idle_texture;
    _idle_texture = idle_texture;
    _runing_texture = run_texture;
    world_position = position;
    sprite_scale = scale;
    width = static_cast<float>(_texture.width) / max_frame;
    height = static_cast<float>(_texture.height);
}

void Character::tick(float delta_time)
{

    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0f;
    }
    if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0f;
    }

    BaseCharacter::tick(delta_time);
}

Vector2 Character::GetScreenPosition() const
{
    return Vector2
    {
        static_cast<float>(_window_width) * 0.5f - sprite_scale * (0.5f * width),
        static_cast<float>(_window_height) * 0.5f - sprite_scale * (0.5f * height)
    };
}
