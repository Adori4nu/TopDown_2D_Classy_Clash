#pragma once
#include "combat.hpp"

#include <string>

enum class ItemType
{
    None,
    Weapon,
    Armor,
    Consumable
};

enum class ConsumableEffects
{
    None,
    Healing,
    Defense,
    Damage
};

class Item
{
public:
    int _id{-1};
    std::string _name{};
    int _texture_id{};

    ItemType _item_type{ItemType::None};
    int _value{};
    float _lifetime{};

    __forceinline bool IsWeapon() const { return _item_type == ItemType::Weapon; }
    __forceinline bool IsArmor() const { return _item_type == ItemType::Armor; }
    __forceinline bool IsActivatable() const { return _item_type == ItemType::Consumable; }

    ConsumableEffects Effect{ConsumableEffects::None};
    float Durration{};

    AttackInformations attack{};
    DefenseInformations defense{};
};

Item* AddItem(const char* name, int sprite, ItemType type);
Item* GetItem(int id);

int GetRandomItem(int except = -1);

void SetupDefaultItems();