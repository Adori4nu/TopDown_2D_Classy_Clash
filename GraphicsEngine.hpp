#pragma once

#include "include/raylib.h"
#include "include/raymath.h"

#include <memory>
#include <vector>

class Actor;
class BaseEnemy;
class BasePlayerCharacter;
class GameObject;
class Pawn;
class Prop;
class World;

class GraphicsEngine
{
public:
    GraphicsEngine(World* world
                , BasePlayerCharacter* player)
                : _world(world)
                , _player_character(player)
                { 
                    // gameObjects.resize(100);
                    // environmentProps.resize(100);
                };
                
    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;
    // static std::shared_ptr<GraphicsEngine> GetInstance() {
    //     if(!instance)
    //         instance = std::make_shared<GraphicsEngine>();
    //     return instance;
    // }

    // static void Initialize(Texture2D& world, BasePlayerCharacter& player)
    // {
    //     instance = std::make_shared<GraphicsEngine>();
    // };

    void AddGameObject(GameObject* gameObject) {
        gameObjects.push_back(gameObject);
    }
    void AddProp(Prop* gameObject) {
        environmentProps.push_back(gameObject);
    }


    void RenderAll();

    void RenderWorld(World* world, Vector2 player_position);

    void Render(Prop* prop, Vector2 player_position);

    void Render(Actor* actor, Vector2 player_position);

    void Render(Pawn* pawn, Vector2 player_position);

    void Render(BaseEnemy* enemy, Vector2 player_position);

    void Render(BasePlayerCharacter* player);
private:
    
    // static std::shared_ptr<GraphicsEngine> instance;
    
    World* _world;
    BasePlayerCharacter* _player_character;
    std::vector<GameObject*> gameObjects;
    std::vector<Prop*> environmentProps;
};