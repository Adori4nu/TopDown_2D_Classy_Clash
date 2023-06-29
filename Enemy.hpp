#pragma once
#include <raylib.h>

#include "BaseCharacter.hpp"
class Character;

class Enemy : public BaseCharacter
{                           
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale, float speed, float damage_per_second);
    virtual void tick(float delta_time) override;
    virtual Vector2 GetScreenPosition() const override;
    void SetTarget(Character* target) { _target = target; };
    
private:
    Character* _target;
    float _damage_per_second{10.f};
    float _radius{25.f};
};