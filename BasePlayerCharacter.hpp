#pragma once
#include "include/raylib.h"

#include <iostream>

#include "combat.hpp"
#include "InputComponent.hpp"
#include "Pawn.hpp"
#include "helperFunctions.hpp"

struct InventoryItem
{
    int ItemId;
    int Quantity;
};
class BasePlayerCharacter : public Pawn
{
public:
    BasePlayerCharacter(
    ObjectType type
    , int window_width
    , int window_height
    , int idle_texture
    , int run_texture
    , float scale
    , float speed
    , int damage
    , int health
    , ParticleSystem& damage_particles
    ) : Pawn(type
            , idle_texture
            , run_texture
            , scale
            , speed
            , damage
            , health
            , damage_particles
            )
    , _window_width(window_width)
    , _window_height(window_height)
    {};
    BasePlayerCharacter(
    ObjectType type
    , int window_width
    , int window_height
    , int idle_texture
    , int run_texture
    , float scale
    , ParticleSystem& damage_particles
    )
    : Pawn(type
    , idle_texture
    , run_texture
    , scale
    )
    , _window_width(window_width), _window_height(window_height)
    {
        _speed = 4.0f;
        _damage = 10;
        _damage_particles = &damage_particles;
        m_Particle.SizeBegin = 6.0f;
        m_Particle.SizeEnd = 1.0f;
        m_Particle.SizeVariation = 0.5f;
        m_Particle.VelocityVariation = {0.0f, 0.0f};
        m_Particle.Damage = _damage;
    };

    void PostInitConstruct(Vector2 position);
    virtual void tick(float delta_time) override;

    Vector2 GetScreenPosition() const;
    Rectangle GetCollisionRectangle() const
    {
        return Rectangle {
            world_position.x + 4 * sprite_scale,
            world_position.y + 4 * sprite_scale,
            (width - 7) * sprite_scale,
            (height - 5) * sprite_scale
        };
    }
    __forceinline Texture2D* GetWeaponTexture() const { return _weapon_texture; };
    __forceinline float GetWeaponScale() const { return _weapon_scale; };
    __forceinline Rectangle GetWeaponCollisionRectangle() const { return _weapon_collision_rectangle; };
    __forceinline Vector2 GetWeaponOrigin() const { return orirgin_of_weapon; };
    __forceinline Vector2 GetWeaponOriginOffset() const { return weapon_origin_offset; };
    __forceinline float GetWeaponRotation() const { return rotation; };

    __forceinline int GetDamage() const { return _damage; };
    __forceinline int GetKillCount() const { return _kill_count; };
    __forceinline void IncreaseKillCount(int increase_by) { _kill_count += increase_by; };
    __forceinline void SetKillCount(int kill_count) { _kill_count = kill_count; };

    __forceinline void SetWeaponTexture(Texture& weapon_texture) { _weapon_texture = &weapon_texture; };

    friend std::ostream& operator<<(std::ostream& os, const BasePlayerCharacter& character) {
        os << static_cast<const Pawn&>(character) << ' '
           << character._weapon_scale << ' ' << character._kill_count;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, BasePlayerCharacter& character) {
        is >> static_cast<Pawn&>(character)
           >> character._weapon_scale >> character._kill_count;
        return is;
    }

    PlayerState _state{PlayerState::IDLE_STATE};
private:
    // Input Component
    InputComponent _inputComponent;
    // Render
    int _window_width{};
    int _window_height{};

    int _equiped_weapon{};
    int _equiped_armor{};

    float _pickup_distance{24.f};
    
    float _attack_range{16.f};
    
    // Weapon
    // CHANGE ALL TEXTURES TO ints so there wouldn't be problem with initialization and classes would be lighter
    Texture2D* _weapon_texture{};
    Rectangle _weapon_collision_rectangle{};
    float _weapon_scale{5.f};
    Vector2 orirgin_of_weapon{};
    Vector2 weapon_origin_offset{};
    float rotation{};
    AttackInformations attack_info{ "Punch", _damage, _damage, _attack_range };
    
    DefenseInformations defense_info{ 4, 4 };
    // Gameplay mechanics
    int _kill_count{};
public:
    float _dodge_length{0.1f};
    float dodge_running_time{};
    int resolve{100};
    float _resolve_point_recharge_rate{0.2f};
    float last_resolve_recharge{};
    DodgeDirection dodge_direction{};
    Camera2D player_camera{Vector2{(float)_window_width/2, (float)_window_height/2}, world_position, 0.0, 1.0};
    
    std::vector<InventoryItem> BackpackContent;
    // event callbacks
    // a callback that takes an int
    typedef void(*ItemCallback)(int);

    // callbacks that the HUD can trigger on inventory
    ItemCallback ActivateItemCallback = nullptr;
    ItemCallback EquipArmorCallback = nullptr;
    ItemCallback EquipWeaponCallback = nullptr;
    ItemCallback DropItemCallback = nullptr;
};