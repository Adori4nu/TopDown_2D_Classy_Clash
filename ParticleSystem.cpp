#include "ParticleSystem.hpp"
#include "Random.hpp"

#include <numbers>
#include <string>

void ParticleSystem::tick(float delta_time)
{
    for (auto& particle : m_ParticlePool)
    {
        if (!particle.Active)
            continue;

        if (particle.LifeRamaining <= 0.0f)
        {
            particle.Active = false;
            continue;
        }

        particle.LifeRamaining -= delta_time;
        particle.Position = {particle.Position.x + particle.Velocity.x * delta_time, particle.Position.y + particle.Velocity.y * delta_time};
        particle.Rotation += 5.f * delta_time;

        float life = particle.LifeRamaining / particle.LifeTime;
        Vector3 rgb = Vector3Lerp(particle.ColorBegin, particle.ColorEnd, life);
        Color color {(unsigned char)rgb.x, (unsigned char)rgb.y, (unsigned char)rgb.z, 255};
        color.a = color.a * life;

        float size = Lerp(particle.SizeEnd, particle.SizeBegin, life);

        switch (particle.type)
        {
        case PLAYER_HIT:
        case PLAYER_CRITICAL_HIT:
        case ENEMY_HIT:
        case ENEMY_CRITITCAL_HIT:
            DrawTextPro(
                GetFontDefault()
                , std::to_string(particle.Damage).c_str()
                , particle.Position
                , particle.CharacterOrigin
                , 0.f, (int)size * 12, 0, color
            );
            break;
        case HEAL:
            DrawTextPro(
                GetFontDefault()
                , std::to_string(particle.Damage).c_str()
                , particle.Position
                , particle.CharacterOrigin
                , 0.f, (int)size * 6, 4, color
            );
            break;
        case MISS:
            DrawTextPro(
                GetFontDefault()
                , particle.Miss
                , particle.Position
                , particle.CharacterOrigin
                , particle.Rotation * 15.f, (int)size * 6, 4, color
            );
            break;
        case DODGE:
            DrawTextPro(
                GetFontDefault()
                , particle.Dodge
                , particle.Position
                , particle.CharacterOrigin
                , particle.Rotation * 15.f, (int)size * 6, 4, color
            );
            break;
        }
    }
}

void ParticleSystem::Emit(const ParticleProps &particleProps)
{
    Particle& particle = m_ParticlePool[m_PoolIndex];
    particle.Active = true;
    particle.type = particleProps.type;
    particle.Damage = particleProps.Damage;

    particle.Position = particleProps.Position;
    particle.CharacterOrigin = particleProps.CharacterOrigin;
    particle.Rotation = Random::Float(0,1) * (float)std::numbers::pi; //Random::Float() * 2.0f * glm::pi<float>(); //std::numbers::pi

    // Velocity
    particle.Velocity = particleProps.Velocity;
    particle.Velocity.x += particleProps.VelocityVariation.x;// * (Random::Float() - 0.5f);
    particle.Velocity.y += particleProps.VelocityVariation.y;// * (Random::Float() - 0.5f);

    switch (particle.type)
    {
    case PLAYER_HIT:
    case PLAYER_CRITICAL_HIT:
    case ENEMY_HIT:
    case ENEMY_CRITITCAL_HIT:
        particle.ColorBegin = {255, 0, 0};
        particle.ColorEnd = {255, 0, 0};
        break;
    case HEAL:
        particle.ColorBegin = {0, 255, 0};
        particle.ColorEnd = {0, 255, 0};
        break;
    case MISS:
        particle.ColorBegin = {255, 255, 0};
        particle.ColorEnd = {255, 255, 0};
        break;
    case DODGE:
        particle.ColorBegin = {255, 255, 255};
        particle.ColorEnd = {0, 0, 0};
        break;
    }

    particle.LifeTime = particleProps.LifeTime;
    particle.LifeRamaining = particleProps.LifeTime;
    particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation;// * (Random::Float() - 0.5f);
    particle.SizeEnd = particleProps.SizeEnd;

    m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}