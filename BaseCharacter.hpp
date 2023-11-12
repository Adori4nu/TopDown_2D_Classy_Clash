#pragma once
#include "include/raylib.h"

#include <iostream>

#include "ParticleSystem.hpp"

class BaseCharacter
{
public:
    virtual void tick(float delta_time);
    __forceinline void UndoMovement() { world_position = world_position_last_frame; };
    int TakeDamage(int damage);
    __forceinline Vector2 GetWorldPosition() const { return world_position; };
    virtual Vector2 GetScreenPosition() const = 0;
    virtual Rectangle GetCollisionRectangle() const
    {
        return Rectangle {
            GetScreenPosition().x,
            GetScreenPosition().y,
            sprite_scale * width,
            sprite_scale * height
        };
    }
    __forceinline Vector2 GetVelocity() const { return velocity; };
    __forceinline int GetHealth() const { return _health; };
    __forceinline ParticleProps GetParticleToEmit() const { return m_Particle; };
    __forceinline bool IsAlive() const { return is_alive; };
    __forceinline void SetIsAlive(bool alive) { is_alive = alive; };
    __forceinline void SetParticleToEmitPosition(Vector2 particle_position) { m_Particle.Position = particle_position; };
    __forceinline void SetParticleToEmitType(Type particle_type) { m_Particle.type = particle_type; };
    
    friend std::ostream& operator<<(std::ostream& os, const BaseCharacter& character) {
        os << character.world_position.x << ' ' << character.world_position.y << ' '
           << character._damage << ' ' << character._health << ' '
           << character.m_Particle.SizeBegin << ' ' << character.m_Particle.SizeEnd << ' '
           << character.m_Particle.SizeVariation << ' ' << character.m_Particle.VelocityVariation.x << ' '
           << character.m_Particle.VelocityVariation.y << ' ' << character.m_Particle.Damage;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, BaseCharacter& character) {
        is >> character.world_position.x >> character.world_position.y
           >> character._damage >> character._health
           >> character.m_Particle.SizeBegin >> character.m_Particle.SizeEnd
           >> character.m_Particle.SizeVariation >> character.m_Particle.VelocityVariation.x
           >> character.m_Particle.VelocityVariation.y >> character.m_Particle.Damage;
        return is;
    }
protected:
    Texture2D _texture{};
    Texture2D _idle_texture{};
    Texture2D _runing_texture{};
    Vector2 world_position{};
    Vector2 world_position_last_frame{};
    Vector2 velocity{};
    float right_left{1.f};
    float running_time{};
    int frame{};
    int max_frame{6};
    float frame_update_time{1.f / 12.f};
    float _speed{4.f};
    float sprite_scale{4.f};
    float width{};
    float height{};
    int _damage{10};
    int _health{100};
    ParticleSystem* _damage_particles;
    ParticleProps m_Particle;
private:
    bool is_alive{true};
};