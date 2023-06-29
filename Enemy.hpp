#pragma once
#include <raylib.h>

#include "BaseCharacter.hpp"
class Character;

class Enemy : public BaseCharacter
{                           
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale);
    virtual void tick(float delta_time) override;
    void SetTarget(Character* target) { _target = target; };
    
private:
    Character* _target;
};