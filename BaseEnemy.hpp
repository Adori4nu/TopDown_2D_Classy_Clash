#pragma once
#include "include/raylib.h"

#include "Pawn.hpp"
#include "EnemyType.hpp"
#include "helperFunctions.hpp"
#include "gameConstants.hpp"

class BasePlayerCharacter;
class ParticleSystem;

enum class EnemyState : short
{
    IDLE,
    PATROLING,
    PURSUING
};

class BaseEnemy : public Pawn
{
    friend class EnemyType;

public:
    virtual void tick(float delta_time) override;
    __forceinline void SetTarget(BasePlayerCharacter* target) { _target = target; };
    __forceinline Rectangle GetCollisionRectangle() const
    {
        return Rectangle {
            world_position.x,
            world_position.y,
            sprite_scale * width,
            sprite_scale * height
        };
    }
    __forceinline Vector2 GetEnemyCenter() const { return Vector2{
        world_position.x + (sprite_scale * width / 2)
        , world_position.y + (sprite_scale * height)};
        };

    __forceinline float GetSightRadius() const { return _sight_radius; };
    __forceinline EnemyState GetEnemyState() const { return enemy_state; };

    Vector2 SetRandomPositionOnCircle(Vector2 cicle_center, float circle_radius=(window_width*0.5));

private:
    BaseEnemy(EnemyType& enemy_type
    ) : Pawn(enemy_type._object_type
        , enemy_type._idle_texture
        , enemy_type._runing_texture
        , enemy_type.sprite_scale
        , enemy_type._speed
        , enemy_type._damage
        , enemy_type._health)
        , enemy_type(enemy_type)
    {
        m_Particle.SizeBegin = 6.0f;
        m_Particle.SizeEnd = 1.0f;
        m_Particle.SizeVariation = 0.5f;
        m_Particle.VelocityVariation = {0.0f, 0.0f};
    }

    EnemyType& enemy_type;
    BasePlayerCharacter* _target;
    float _radius{25.f}; // attack radius
    float _attack_speed{1.f/(_speed * 0.5f)};
    bool character_in_range{false};
    float character_in_range_time{};
    // Follow logic
    float _sight_radius{5*32.f};
    EnemyState enemy_state{EnemyState::IDLE};
    // Vector2 enemy_center{};
    float _patrol_radius{8*32.f};
};