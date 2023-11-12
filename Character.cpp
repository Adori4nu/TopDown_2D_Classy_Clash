#include "Character.hpp"
#include <bits/stdc++.h> 
#include "include/raymath.h"

Character::Character(
    int window_width
    , int window_height
    , Texture2D idle_texture
    , Texture2D run_texture
    , float scale
    , ParticleSystem& damage_particles
    ) : _window_width(window_width), _window_height(window_height)
{
    _texture = idle_texture;
    _idle_texture = idle_texture;
    _runing_texture = run_texture;
    sprite_scale = scale;
    width = static_cast<float>(_texture.width) / max_frame;
    height = static_cast<float>(_texture.height);
    _damage_particles = &damage_particles;
}

Character::Character(
    int window_width
    , int window_height
    , Texture2D idle_texture
    , Texture2D run_texture
    , Vector2 position
    , float scale
    , ParticleSystem& damage_particles
    ) : _window_width(window_width), _window_height(window_height)
{
    _texture = idle_texture;
    _idle_texture = idle_texture;
    _runing_texture = run_texture;
    world_position = position;
    sprite_scale = scale;
    width = static_cast<float>(_texture.width) / max_frame;
    height = static_cast<float>(_texture.height);
    _damage = 20;
    _health = 100;
    _damage_particles = &damage_particles;
    m_Particle.SizeBegin = 6.0f;
    m_Particle.SizeEnd = 1.0f;
    m_Particle.SizeVariation = 0.5f;
    m_Particle.VelocityVariation = {0.0f, 0.0f};
    m_Particle.Damage = _damage;
}

void Character::PostInitConstruct(Vector2 position)
{
    world_position = position;
    _damage = 20;
    _health = 100;
    m_Particle.SizeBegin = 6.0f;
    m_Particle.SizeEnd = 1.0f;
    m_Particle.SizeVariation = 0.5f;
    m_Particle.VelocityVariation = {0.0f, 0.0f};
    m_Particle.Damage = _damage;
}

void Character::tick(float delta_time)
{
    if (!IsAlive())
    {
        return;
    }
    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0f;
    }
    if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0f;
    }

    BaseCharacter::tick(delta_time);

    Vector2 orirgin_of_weapon{};
    Vector2 weapon_origin_offset{};
    float rotation{};
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


    Rectangle source{0.0f, 0.0f, static_cast<float>(_weapon_texture.width) * right_left, static_cast<float>(_weapon_texture.height)};
    Rectangle dest{GetScreenPosition().x + weapon_origin_offset.x, GetScreenPosition().y + weapon_origin_offset.y, static_cast<float>(_weapon_texture.width) * _weapon_scale, static_cast<float>(_weapon_texture.height) * _weapon_scale};
    DrawTexturePro(_weapon_texture, source, dest, orirgin_of_weapon, rotation, WHITE);
    DrawRectangleLines(GetCollisionRectangle().x
    , GetCollisionRectangle().y
    , GetCollisionRectangle().width
    , GetCollisionRectangle().height
    , GREEN
    );
}

Vector2 Character::GetScreenPosition() const
{
    return Vector2
    {
        static_cast<float>(_window_width) * 0.5f - sprite_scale * (0.5f * width),
        static_cast<float>(_window_height) * 0.5f - sprite_scale * (0.5f * height)
    };
}
