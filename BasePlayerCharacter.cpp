#include "BasePlayerCharacter.hpp"
#include "Pawn.hpp"

#include <bits/stdc++.h>

#include "include/raymath.h"

void BasePlayerCharacter::PostInitConstruct(Vector2 position)
{
    SetWorldPosition(position);
    _damage = 20;
    m_Particle.SizeBegin = 6.0f;
    m_Particle.SizeEnd = 1.0f;
    m_Particle.SizeVariation = 0.5f;
    m_Particle.VelocityVariation = {0.0f, 0.0f};
    m_Particle.Damage = _damage;
}

void BasePlayerCharacter::tick(float delta_time)
{
    if (!_healthComponent.is_alive)
    {
        return;
    }
    
    last_resolve_recharge += delta_time;
    if (last_resolve_recharge >= _resolve_point_recharge_rate && resolve < 100)
    {
        last_resolve_recharge = {};
        ++resolve;
    }
    velocity = {};
    
    _inputComponent.update(*this);

    world_position_last_frame = GetWorldPosition();

    Actor::tick(delta_time);

    if (Vector2Length(velocity) != 0)
    {
        if(_state == PlayerState::DODGING_STATE)
        {
            dodge_running_time += delta_time;
            SetWorldPosition(Vector2Add(world_position, Vector2Scale(Vector2Normalize(velocity), _speed*2.5f)));
        }
        else
        {
            SetWorldPosition(Vector2Add(world_position, Vector2Scale(Vector2Normalize(velocity), _speed)));
        }
        velocity.x < 0.f ? right_left = -1.f : right_left = 1.f;
    }

    // this is bad we cant attack without weapon and origin of weapon is in wrong place
    if (!_weapon_texture)
        return;
    if (right_left > 0.f)
    {
        orirgin_of_weapon = Vector2{0.0f, _weapon_texture->height * _weapon_scale};
        weapon_origin_offset = Vector2{35.f, 50.f};
        _weapon_collision_rectangle = 
        {
            world_position.x + weapon_origin_offset.x,
            world_position.y + weapon_origin_offset.y - _weapon_texture->height * _weapon_scale,
            _weapon_texture->width * _weapon_scale,
            _weapon_texture->height * _weapon_scale
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 45.f : -15.f;
    }
    else
    {
        orirgin_of_weapon = Vector2{_weapon_texture->width * _weapon_scale, _weapon_texture->height * _weapon_scale};
        weapon_origin_offset = Vector2{25.f, 50.f};
        _weapon_collision_rectangle = 
        {
            world_position.x + weapon_origin_offset.x - _weapon_texture->width * _weapon_scale,
            world_position.y + weapon_origin_offset.y - _weapon_texture->height * _weapon_scale,
            _weapon_texture->width * _weapon_scale,
            _weapon_texture->height * _weapon_scale
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -45.f : 15.f;
    }

    // if (player_character.GetWorldPosition().x < (0.f - 32.f*3 - 8.f) * ASSET_SCALE ||
    //     player_character.GetWorldPosition().y < (0.f - 32.f*1 - 8.f) * ASSET_SCALE ||
    //     player_character.GetWorldPosition().x + window_width > (map_texture.width + 32.f*4 - 24.f) * ASSET_SCALE ||
    //     player_character.GetWorldPosition().y + window_height > (map_texture.height + 32.f*2 - 24.f) * ASSET_SCALE
    // )
    // {
    //     player_character.UndoMovement();
    // }
    
}

Vector2 BasePlayerCharacter::GetScreenPosition() const
{
    return Vector2
    {
        static_cast<float>(_window_width) * 0.5f - sprite_scale * (0.5f * width),
        static_cast<float>(_window_height) * 0.5f - sprite_scale * (0.5f * height)
    };
}

void ActivateItem(int item)
{

}

void DropItem(int item)
{

}