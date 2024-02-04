#pragma once
#include "include/raylib.h"

#include "ParticleSystem.hpp"
#include "GraphicsComponent.hpp"
#include "GameObject.hpp"
class BaseEnemy;

class EnemyType
{
public:
    EnemyType(ObjectType type
            , EnemyType* parent
            , int idle_texture
            , int run_texture
            , float scale
            , float speed
            , int damage
            , int health
            )
            : _object_type(type)
            , _idle_texture(idle_texture)
            , _runing_texture(run_texture)
            , sprite_scale(scale)
            , _speed(speed)
            , _damage(damage)
            , _health(health)
            {};
    BaseEnemy* newEnemy();
    
    ObjectType _object_type;
    EnemyType* _parent;
    // Render
    int _idle_texture{};
    int _runing_texture{};
    float sprite_scale{4.f};
    // Stats
    float _speed{};
    int _damage{};
    int _health{};
private:
};