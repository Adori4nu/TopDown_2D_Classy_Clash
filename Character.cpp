#include "Character.hpp"
#include <raymath.h>

Character::Character(int window_width, int window_height, Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale)
{
    _texture = idle_texture;
    _idle_texture = idle_texture;
    _runing_texture = run_texture;
    world_position = position;
    sprite_scale = scale;
    width = static_cast<float>(_texture.width) / max_frame;
    height = static_cast<float>(_texture.height);
    screen_position = {
    static_cast<float>(window_width) * 0.5f - sprite_scale * (0.5f * width),
    static_cast<float>(window_height) * 0.5f - sprite_scale * (0.5f * height)
    };
}

void Character::tick(float delta_time)
{
    BaseCharacter::tick(delta_time);

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
        _texture = _runing_texture;
    }
    else
    {
        _texture = _idle_texture;
    }
}
