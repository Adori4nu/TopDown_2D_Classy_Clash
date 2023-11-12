#pragma once
#include "include/raylib.h"

#include "BaseCharacter.hpp"
class Character;

class Enemy : public BaseCharacter
{                           
public:
    Enemy(Texture2D idle_texture
        , Texture2D run_texture
        , Vector2 position
        , float scale
        , float speed
        , int damage
        , int health
        , ParticleSystem& damage_particles
        );
    virtual void tick(float delta_time) override;
    virtual Vector2 GetScreenPosition() const override;
    void SetTarget(Character* target) { _target = target; };
    virtual Rectangle GetCollisionRectangle() const override
    {
        return Rectangle {
            GetScreenPosition().x,
            GetScreenPosition().y,
            sprite_scale * width,
            sprite_scale * height
        };
    }
    
private:
    Character* _target;
    float _radius{25.f};
    float _attack_speed{1.f/(_speed * 0.5f)};
    bool character_in_range{false};
    float character_in_range_time{};
};