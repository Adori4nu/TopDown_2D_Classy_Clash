#pragma once
#include <raylib.h>

#include "BaseCharacter.hpp"

class Character : public BaseCharacter
{
public:
    Character(int window_width, int window_height, Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale);

    virtual void tick(float delta_time) override;
    virtual Vector2 GetScreenPosition() const override;
    Rectangle GetWeaponCollisionRectangle() const { return _weapon_collision_rectangle; };
    float GetHealth() const { return _health; };
    void TakeDamage(float damage);
    ~Character() 
    {
        UnloadTexture(_texture); 
        UnloadTexture(_idle_texture);
        UnloadTexture(_runing_texture);
        UnloadTexture(_weapon_texture); 
    };
private:
    int _window_width{};
    int _window_height{};
    Texture2D _weapon_texture{LoadTexture("textures/characters/weapon_sword.png")};
    Rectangle _weapon_collision_rectangle{};
    float _weapon_scale{2.5f};
    float _health{100.f};
};