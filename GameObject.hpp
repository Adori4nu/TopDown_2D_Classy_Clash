#pragma once
#include "include/raylib.h"
#include "include/raymath.h"

#include <iostream>

#include "World.hpp"

enum class ObjectType : uint16_t
{
    Game_Object,
    Actor,
    Pawn,
    Base_Enemy,
    Base_Player,
    Prop,
};

class GameObject
{
    friend class World;
public:
    GameObject(ObjectType type, Vector2 world_pos)
    : _object_type(type)
    , world_position(world_pos)
    {};
    GameObject(ObjectType type)
    : _object_type(type)
    {};

    ObjectType GetObjectType() const { return _object_type; }

    Vector2 GetWorldPosition() const { return world_position; };
    World& GetWorld() const { return *_world; };

    void SetWorldPosition(Vector2 world_pos) { world_position = world_pos; };
    void SetWorld(World& world) { _world = &world; _world->Add(this); };

    friend std::ostream& operator<<(std::ostream& os, const GameObject& character) {
        os /*<< character._object_type << ' '*/ << character.world_position.x << ' ' << character.world_position.y;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, GameObject& character) {
        is /*>> character._object_type*/ >> character.world_position.x >> character.world_position.y;
        return is;
    }

protected:
    ObjectType _object_type;
    World* _world;
    Vector2 world_position{};
private:
};

