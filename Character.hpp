#pragma once
#include "include/raylib.h"

#include <iostream>

#include "BaseCharacter.hpp"

class Character : public BaseCharacter
{
public:
    Character(int window_width, int window_height, Texture2D idle_texture, Texture2D run_texture, float scale, ParticleSystem& damage_particles);
    Character(int window_width, int window_height, Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale, ParticleSystem& damage_particles);

    void PostInitConstruct(Vector2 position);
    virtual void tick(float delta_time) override;
    virtual Vector2 GetScreenPosition() const override;
    Rectangle GetWeaponCollisionRectangle() const { return _weapon_collision_rectangle; };
    virtual Rectangle GetCollisionRectangle() const override
    {
        return Rectangle {
            GetScreenPosition().x + 4 * sprite_scale,
            GetScreenPosition().y + 4 * sprite_scale,
            (width - 7) * sprite_scale,
            (height - 5) * sprite_scale
        };
    }
    __forceinline int GetDamage() const { return _damage; };
    __forceinline int GetKillCount() const { return _kill_count; };
    __forceinline void IncreaseKillCount(int increase_by) { _kill_count += increase_by; };
    __forceinline void SetKillCount(int kill_count) { _kill_count = kill_count; };

    friend std::ostream& operator<<(std::ostream& os, const Character& character) {
        os << static_cast<const BaseCharacter&>(character) << ' '
           << character._weapon_scale << ' ' << character._kill_count;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Character& character) {
        is >> static_cast<BaseCharacter&>(character)
           >> character._weapon_scale >> character._kill_count;
        return is;
    }

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
    float _weapon_scale{5.f};
    int _kill_count{};
};