#pragma once
#include <raylib.h>

class Prop
{
public:
    Prop(const Vector2& world_position, Texture2D& texture, float sprite_scale);
    Vector2 CalculateScreenPosition(Vector2 player_position) const;
    void Render(Vector2 player_position);
    Rectangle GetCollisionRectangle(Vector2 player_position) const;
private:
    Texture2D texture{};
    Vector2 world_position{};
    float sprite_scale{4.f};
};