#include "Enemy.hpp"
#include "Character.hpp"
#include "Random.hpp"

#include "include/raymath.h"


Enemy::Enemy(Texture2D idle_texture
            , Texture2D run_texture
            , Vector2 position
            , float scale
            , float speed
            , int damage
            , int health
            , ParticleSystem& damage_particles
    )
{
    _texture = idle_texture;
    _idle_texture = idle_texture;
    _runing_texture = run_texture;
    world_position = position;
    sprite_scale = scale;
    width = static_cast<float>(_texture.width) / max_frame;
    height = static_cast<float>(_texture.height);
    _speed = speed;
    _damage = damage;
    _health = health;
    _damage_particles = &damage_particles;
    m_Particle.SizeBegin = 6.0f;
    m_Particle.SizeEnd = 1.0f;
    m_Particle.SizeVariation = 0.5f;
    m_Particle.VelocityVariation = {0.0f, 0.0f};
}

void Enemy::tick(float delta_time)
{
    if (!_target || !IsAlive())
    {
        return;
    }
    velocity = Vector2Subtract(_target->GetScreenPosition(), GetScreenPosition());
   
    if (Vector2Length(velocity) < _radius)
    {
        velocity = {};
    }

    BaseCharacter::tick(delta_time);

    if (CheckCollisionRecs(GetCollisionRectangle(), _target->GetCollisionRectangle()))
    {
        character_in_range = true;
        character_in_range_time += delta_time;
        if (character_in_range_time >= _attack_speed)
        {
            if (Random::Float() * 100 > 50)
            {
                m_Particle.Damage = _target->TakeDamage(_damage);
                m_Particle.type = Type::PLAYER_HIT;
            }
            else
            {
                m_Particle.type = Type::MISS;
            }
            SetParticleToEmitPosition({_target->GetScreenPosition().x + 6*4.f, _target->GetScreenPosition().y - 6 * 4.f});
            m_Particle.Velocity = _target->GetVelocity();
            _damage_particles->Emit(m_Particle);
            character_in_range = false;
            character_in_range_time = 0.f;
        }
    }
    else
    {
        character_in_range = false;
        character_in_range_time = 0.f;
    }
    DrawRectangleLines(GetScreenPosition().x
    , GetScreenPosition().y
    , static_cast<float>(_texture.width) / max_frame * sprite_scale
    , _texture.height * sprite_scale
    , RED)
    ;
}

Vector2 Enemy::GetScreenPosition() const
{
    return Vector2Subtract(world_position, _target->GetWorldPosition());
}