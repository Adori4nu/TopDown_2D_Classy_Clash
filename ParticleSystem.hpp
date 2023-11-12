#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "include/raylib.h"
#include "include/raymath.h"

enum Type : uint8_t
{
    PLAYER_HIT = 0,
    PLAYER_CRITICAL_HIT = 1,

    ENEMY_HIT = 2,
    ENEMY_CRITITCAL_HIT = 3,

    HEAL = 4,

    MISS = 5,
    DODGE = 6,
};

struct ParticleProps
{
    Type type;
    int Damage;
    Vector2 Position, CharacterOrigin {0.f, 0.f};
    Vector2 Velocity, VelocityVariation {0.f, 0.f};
    Vector3 ColorBegin, ColorEnd;
    float SizeBegin, SizeEnd, SizeVariation;
    float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
    ParticleSystem(){ m_ParticlePool.resize(100); };

    void tick(float delta_time);

    // void Render();

    void Emit(const ParticleProps& particleProps);

private:
    struct Particle
    {
        Type type;
        int Damage;
        const char* Miss = "Miss";
        const char* Dodge = "Dodge";
        
        Vector2 Position;
        Vector2 CharacterOrigin;
        Vector2 Velocity;
        Vector3 ColorBegin, ColorEnd;

        float Rotation = 0.0f;
        float SizeBegin, SizeEnd;

        float LifeTime = 2.0f;
        float LifeRamaining = 0.0f;

        bool Active = false;
    };

    std::vector<Particle> m_ParticlePool;
    uint32_t m_PoolIndex = 99;
};