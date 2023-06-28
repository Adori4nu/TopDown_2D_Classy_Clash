#include "Enemy.hpp"
#include <raymath.h>

Enemy::Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale) :
    texture(idle_texture),
    idle_texture(idle_texture),
    runing_texture(run_texture),
    world_position(position),
    sprite_scale(scale)
{
    width = static_cast<float>(texture.width) / max_frame;
    height = static_cast<float>(texture.height);
}

void Enemy::tick(float delta_time)
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
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

Rectangle Enemy::GetCollisionRectangle() const
{
    return Rectangle {
        screen_position.x,
        screen_position.y,
        sprite_scale * width,
        sprite_scale * height
    };
}
