#include "BaseEnemy.hpp"
#include "BasePlayerCharacter.hpp"
#include "Random.hpp"

#include "include/raymath.h"

void BaseEnemy::tick(float delta_time)
{
    if (!_target || !IsAlive())
    {
        return;
    }

    // Vector2 enemy_position_center = GetEnemyCenter();
    // DrawCircleLines(enemy_position_center.x
    //         , enemy_position_center.y
    //         , _sight_radius
    //         , YELLOW
    //         );
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

    Pawn::tick(delta_time);

    if (CheckCollisionRecs(GetCollisionRectangle(), _target->GetCollisionRectangle()))
    {
        character_in_range = true;
        character_in_range_time += delta_time;
        if (character_in_range_time >= _attack_speed)
        {
            if (Random::Float(1,100) > 50)
            {
                m_Particle.Damage = _target->TakeDamage(_damage);
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

Vector2 BaseEnemy::GetScreenPosition() const
{
    return Vector2Subtract(GetWorldPosition(), _target->GetWorldPosition());
}
