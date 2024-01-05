#pragma once

#include "Actor.hpp"
#include "ParticleSystem.hpp"
#include "HealthComponent.hpp"

#include <iostream>

enum class PawnState : short
{
    IDLE_STATE,
    WALKING_STATE,
    ATACKING_STATE,
    DODGING_STATE,
    HITED_STATE
};

enum class DodgeDirection : short
{
    DODGE_LEFT,
    DODGE_LEFT_UP,
    DODGE_LEFT_DOWN,
    DODGE_RIGHT,
    DODGE_RIGHT_UP,
    DODGE_RIGHT_DOWN,
    DODGE_UP,
    DODGE_DOWN
};

class Pawn : public Actor
{
public:
    Pawn(ObjectType type
        , Texture2D idle_texture
        , Texture2D run_texture
        , float scale
        , float speed
        , int damage
        , int health
        , ParticleSystem& damage_particles
        ) 
        : Actor(type
        , idle_texture
        , scale
        )
        , _runing_texture(run_texture)
        , _speed(speed)
        , _damage(damage)
        , _damage_particles(&damage_particles)
        , _healthComponent(health)
        {};
    Pawn(ObjectType type
        , Texture2D idle_texture
        , Texture2D run_texture
        , float scale
        , float speed
        , int damage
        , int health
        ) 
        : Actor(type
        , idle_texture
        , scale
        )
        , _runing_texture(run_texture)
        , _speed(speed)
        , _damage(damage)
        , _healthComponent(health)
        {};
    Pawn(ObjectType type
        , Texture2D idle_texture
        , Texture2D run_texture
        , float scale
        ) 
        : Actor(type
        , idle_texture
        , scale
        )
        , _runing_texture(run_texture)
        {};
    virtual void tick(float delta_time) override;

    __forceinline void UndoMovement() { world_position = world_position_last_frame; };

    __forceinline Vector2 GetVelocity() const { return velocity; };
    
    __forceinline void SetVelocity(Vector2 update_velocity) 
    { 
        velocity.x += update_velocity.x;
        velocity.y += update_velocity.y;
    };

    __forceinline ParticleProps GetParticleToEmit() const { return m_Particle; };
    __forceinline void SetParticleToEmitPosition(Vector2 particle_position) { m_Particle.Position = particle_position; };
    __forceinline void SetParticleToEmitType(Type particle_type) { m_Particle.type = particle_type; };

    __forceinline void SetParticleSystem(ParticleSystem& particle_system) { _damage_particles = &particle_system; };

    __forceinline Vector2 GetWorldPositionLastFrame() const { return world_position_last_frame; };

    friend std::ostream& operator<<(std::ostream& os, const Pawn& character) {
        os << static_cast<const Actor&>(character) << ' '
           << character._healthComponent._max_health << ' ' << character._healthComponent._current_health << ' ' << character._damage  << ' '
           << character.m_Particle.SizeBegin << ' ' << character.m_Particle.SizeEnd << ' '
           << character.m_Particle.SizeVariation << ' ' << character.m_Particle.VelocityVariation.x << ' '
           << character.m_Particle.VelocityVariation.y << ' ' << character.m_Particle.Damage;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Pawn& character) {
        is >> static_cast<Actor&>(character)
           >> character._healthComponent._max_health >> character._healthComponent._current_health >> character._damage
           >> character.m_Particle.SizeBegin >> character.m_Particle.SizeEnd
           >> character.m_Particle.SizeVariation >> character.m_Particle.VelocityVariation.x
           >> character.m_Particle.VelocityVariation.y >> character.m_Particle.Damage;
        return is;
    }

    HealthComponent& GetHealthComponent() { return _healthComponent; };
    
    PawnState _state{PawnState::IDLE_STATE};
    // Components
protected:
    // Render
    Texture2D _runing_texture{};
    Vector2 world_position_last_frame{};
    Vector2 velocity{};
    // Stats
    float _speed{4.f};
    int _damage{10};
public:
protected:
    HealthComponent _healthComponent;
    // Particles
    ParticleSystem* _damage_particles;
    ParticleProps m_Particle;
private:
    // Game logic

};