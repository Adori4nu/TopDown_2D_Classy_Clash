#include "InputComponent.hpp"

#include "BasePlayerCharacter.hpp"

#include <iostream>

#include "include/raymath.h"

void InputComponent::update(BasePlayerCharacter& player)
{
    if (IsKeyDown(KEY_A))
    {
        player.SetVelocity(Vector2{-1.0f, 0.f}); // .x -= 1.0f
    }
    if (IsKeyDown(KEY_D))
    {
        player.SetVelocity(Vector2{1.0f, 0.f});
    }
    if (IsKeyDown(KEY_W))
    {
        player.SetVelocity(Vector2{0.f, -1.f});
    }
    if (IsKeyDown(KEY_S))
    {
        player.SetVelocity(Vector2{0.f, 1.f});
    }
}