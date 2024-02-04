#include "BaseEnemy.hpp"
#include "BasePlayerCharacter.hpp"
#include "Random.hpp"
#include "Game.hpp"

#include "include/raymath.h"

#include <numbers>

void BaseEnemy::tick(float delta_time)
{
    if (!_target || !_healthComponent.is_alive)
    {
        return;
    }
    if(GetSceneType() == SceneType::STORY_MODE)
        if(CheckCollisionCircleRec(GetEnemyCenter(), _sight_radius, _target->GetCollisionRectangle()))
        {
            enemy_state = EnemyState::PURSUING;
            velocity = Vector2Subtract(_target->GetWorldPosition(), GetWorldPosition());
        
            if (Vector2Length(velocity) < _radius)
            {
                velocity = {};
            }
        }
        else
        {
            enemy_state = EnemyState::IDLE;
        }
    else
    {
        velocity = Vector2Subtract(_target->GetWorldPosition(), GetWorldPosition());

        if (Vector2Length(velocity) < _radius)
        {
            velocity = {};
        }
    }
    

    Pawn::tick(delta_time);

    if (CheckCollisionRecs(GetCollisionRectangle(), _target->GetCollisionRectangle()))
    {
        character_in_range = true;
        character_in_range_time += delta_time;
        if (character_in_range_time >= _attack_speed)
        {
            if (Random::Float(1,100) > 50)
            {
                m_Particle.Damage = _damage;
                _target->GetHealthComponent().TakeDamage(_damage);
                m_Particle.type = Type::PLAYER_HIT;
            }
            else
            {
                m_Particle.type = Type::MISS;
            }
            SetParticleToEmitPosition({_target->GetWorldPosition().x + 6*4.f, _target->GetWorldPosition().y - 6 * 4.f});
            m_Particle.Velocity = _target->GetVelocity();
            _damage_particles->Emit(m_Particle);
            character_in_range = false;
            character_in_range_time = {};
        }
    }
    else
    {
        character_in_range = false;
        character_in_range_time = {};
    }
}

Vector2 BaseEnemy::SetRandomPositionOnCircle(Vector2 cicle_center, float circle_radius)
{
    float angle = Random::Float(0, 1) / 2.f * std::numbers::pi;
    return Vector2{
        cicle_center.x + circle_radius * (Random::Float(0,1) > 0.5f ? std::cos(angle) : (-1.f * std::cos(angle)))
        , cicle_center.y + circle_radius * (Random::Float(0,1) > 0.5f ? std::sin(angle) : (-1.f * std::sin(angle)))
    };
}
