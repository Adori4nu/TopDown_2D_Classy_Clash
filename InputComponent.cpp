#include "InputComponent.hpp"

#include "BasePlayerCharacter.hpp"

#include <iostream>

#include "include/raymath.h"

void InputComponent::update(BasePlayerCharacter& player)
{
    using enum PlayerState;
    using enum DodgeDirection;
    switch (player._state)
    {
    case IDLE_STATE:
        if (IsKeyDown(KEY_A))
        {
            player._state = WALKING_STATE;
            player.SetVelocity(Vector2{-1.0f, 0.f});
        }
        if (IsKeyDown(KEY_D))
        {
            player._state = WALKING_STATE;
            player.SetVelocity(Vector2{1.0f, 0.f});
        }
        if (IsKeyDown(KEY_W))
        {
            player._state = WALKING_STATE;
            player.SetVelocity(Vector2{0.f, -1.f});
        }
        if (IsKeyDown(KEY_S))
        {
            player._state = WALKING_STATE;
            player.SetVelocity(Vector2{0.f, 1.f});
        }
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_LEFT_UP;
            player.SetVelocity(Vector2{-1.0f, -1.f});
            break;
        }
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_RIGHT_UP;
            player.SetVelocity(Vector2{1.0f, -1.f});
            break;
        }
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_LEFT_DOWN;
            player.SetVelocity(Vector2{-1.f, 1.f});
            break;
        }
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_RIGHT_DOWN;
            player.SetVelocity(Vector2{1.f, 1.f});
            break;
        }
        if (IsKeyDown(KEY_A) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_LEFT;
            player.SetVelocity(Vector2{-1.0f, 0.f});
            break;
        }
        if (IsKeyDown(KEY_D) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_RIGHT;
            player.SetVelocity(Vector2{1.0f, 0.f});
            break;
        }
        if (IsKeyDown(KEY_W) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_UP;
            player.SetVelocity(Vector2{0.f, -1.f});
            break;
        }
        if (IsKeyDown(KEY_S) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_DOWN;
            player.SetVelocity(Vector2{0.f, 1.f});
            break;
        }
        break;
    case WALKING_STATE:
        if (IsKeyDown(KEY_A))
        {
            player.SetVelocity(Vector2{-1.0f, 0.f});
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
        if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_S) && IsKeyUp(KEY_W))
        {
            player._state = IDLE_STATE;
        }
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_LEFT_UP;
            player.SetVelocity(Vector2{-1.0f, -1.f});
            break;
        }
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_RIGHT_UP;
            player.SetVelocity(Vector2{1.0f, -1.f});
            break;
        }
        if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_LEFT_DOWN;
            player.SetVelocity(Vector2{-1.f, 1.f});
            break;
        }
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_RIGHT_DOWN;
            player.SetVelocity(Vector2{1.f, 1.f});
            break;
        }
        if (IsKeyDown(KEY_A) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_LEFT;
            player.SetVelocity(Vector2{-1.0f, 0.f});
            break;
        }
        if (IsKeyDown(KEY_D) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_RIGHT;
            player.SetVelocity(Vector2{1.0f, 0.f});
            break;
        }
        if (IsKeyDown(KEY_W) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_UP;
            player.SetVelocity(Vector2{0.f, -1.f});
            break;
        }
        if (IsKeyDown(KEY_S) && IsKeyPressed(KEY_SPACE) && player.resolve >= 20)
        {
            player._state = DODGING_STATE;
            player.dodge_direction = DODGE_DOWN;
            player.SetVelocity(Vector2{0.f, 1.f});
            break;
        }
        break;
    case DODGING_STATE:
        if(player.dodge_running_time >= player._dodge_length)
        {
            player.dodge_running_time = {};
            player.resolve -= 20;
            player._state = WALKING_STATE;
            break;
        }
        if (player.dodge_direction == DODGE_LEFT_UP)
        {
            player.SetVelocity(Vector2{-1.0f, -1.f});
            break;
        }
        if (player.dodge_direction == DODGE_RIGHT_UP)
        {
            player.SetVelocity(Vector2{1.0f, -1.f});
            break;
        }
        if (player.dodge_direction == DODGE_LEFT_DOWN)
        {
            player.SetVelocity(Vector2{-1.f, 1.f});
            break;
        }
        if (player.dodge_direction == DODGE_RIGHT_DOWN)
        {
            player.SetVelocity(Vector2{1.f, 1.f});
            break;
        }
        if (player.dodge_direction == DODGE_LEFT)
        {
            player.SetVelocity(Vector2{-1.0f, 0.f});
            break;
        }
        if (player.dodge_direction == DODGE_RIGHT)
        {
            player.SetVelocity(Vector2{1.0f, 0.f});
            break;
        }
        if (player.dodge_direction == DODGE_UP)
        {
            player.SetVelocity(Vector2{0.f, -1.f});
            break;
        }
        if (player.dodge_direction == DODGE_DOWN)
        {
            player.SetVelocity(Vector2{0.f, 1.f});
            break;
        }
        break;
    default:
        break;
    }
}