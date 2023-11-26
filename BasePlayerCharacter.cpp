#include "BasePlayerCharacter.hpp"
#include "Pawn.hpp"

#include <bits/stdc++.h>

#include "include/raymath.h"

void BasePlayerCharacter::PostInitConstruct(Vector2 position)
{
    SetWorldPosition(position);
    _damage = 20;
    _health = 100;
    m_Particle.SizeBegin = 6.0f;
    m_Particle.SizeEnd = 1.0f;
    m_Particle.SizeVariation = 0.5f;
    m_Particle.VelocityVariation = {0.0f, 0.0f};
    m_Particle.Damage = _damage;
}

void BasePlayerCharacter::tick(float delta_time)
{
    if (!IsAlive())
    {
        return;
    }
    
    _inputComponent.update(*this);

    Pawn::tick(delta_time);

    if (right_left > 0.f)
    {
        orirgin_of_weapon = Vector2{0.0f, _weapon_texture.height * _weapon_scale};
        weapon_origin_offset = Vector2{35.f, 50.f};
        _weapon_collision_rectangle = 
        {
            GetScreenPosition().x + weapon_origin_offset.x,
            GetScreenPosition().y + weapon_origin_offset.y - _weapon_texture.height * _weapon_scale,
            _weapon_texture.width * _weapon_scale,
            _weapon_texture.height * _weapon_scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 45.f : -15.f;
    }
    else
    {
        orirgin_of_weapon = Vector2{_weapon_texture.width * _weapon_scale, _weapon_texture.height * _weapon_scale};
        weapon_origin_offset = Vector2{25.f, 50.f};
        _weapon_collision_rectangle = 
        {
            GetScreenPosition().x + weapon_origin_offset.x - _weapon_texture.width * _weapon_scale,
            GetScreenPosition().y + weapon_origin_offset.y - _weapon_texture.height * _weapon_scale,
            _weapon_texture.width * _weapon_scale,
            _weapon_texture.height * _weapon_scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -45.f : 15.f;
    }
    
}

Vector2 BasePlayerCharacter::GetScreenPosition() const
{
    return Vector2
    {
        static_cast<float>(_window_width) * 0.5f - sprite_scale * (0.5f * width),
        static_cast<float>(_window_height) * 0.5f - sprite_scale * (0.5f * height)
    };
}
