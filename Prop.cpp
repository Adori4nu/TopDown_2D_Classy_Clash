#include "Prop.hpp"
#include <raylib.h>
#include <raymath.h>

Prop::Prop(const Vector2& world_position, Texture2D& texture, float sprite_scale)
    : texture{texture}, world_position{world_position}, sprite_scale{sprite_scale}
{
}

void Prop::Render(Vector2 player_position)
{
    Vector2 screen_position {Vector2Subtract(world_position, player_position)};
    DrawTextureEx(texture, screen_position, 0.f, sprite_scale, WHITE);
    DrawRectangleLines(screen_position.x
    , screen_position.y
    , static_cast<float>(texture.width) * sprite_scale
    , texture.height * sprite_scale
    , BLUE
    );
}

Rectangle Prop::GetCollisionRectangle(Vector2 player_position) const
{
    Vector2 screen_position {Vector2Subtract(world_position, player_position)};
    return Rectangle {
        screen_position.x,
        screen_position.y,
        static_cast<float>(texture.width) * sprite_scale,
        static_cast<float>(texture.height) * sprite_scale
    };
}

