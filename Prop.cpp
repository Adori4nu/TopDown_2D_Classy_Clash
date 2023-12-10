#include "Prop.hpp"
#include <raylib.h>
#include <raymath.h>


Rectangle Prop::GetCollisionRectangle() const
{
    // Vector2 screen_position {Vector2Subtract(world_position, player_position)};
    return Rectangle {
        world_position.x,
        world_position.y,
        static_cast<float>(texture.width) * sprite_scale,
        static_cast<float>(texture.height) * sprite_scale
    };
}

