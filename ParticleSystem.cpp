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