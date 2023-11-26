#include "Prop.hpp"
#include <raylib.h>
#include <raymath.h>


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

