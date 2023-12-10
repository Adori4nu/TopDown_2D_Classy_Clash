#pragma once

#include "include/raylib.h"
#include "include/raymath.h"

#include <memory>
#include <vector>

#include "BasePlayerCharacter.hpp"

// class Actor;
class BaseEnemy;
// class BasePlayerCharacter;
class GameObject;
// class Pawn;
class Prop;
class World;

class GraphicsEngine
{
public:
    GraphicsEngine(int window_width
                , int window_height
                , World* world
                , BasePlayerCharacter* player
                , ParticleSystem* particle_system)
                : _window_width(window_width)
                , _window_height(window_height)
                , _world(world)
                , _player_character(player)
                , _particle_system(particle_system)
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

    void RenderWorld(World* world);

    void Render(Prop* prop);

    void Render(Actor* actor);

    void Render(Pawn* pawn);

    void Render(BaseEnemy* enemy);

    void Render(BasePlayerCharacter* player);

    void Render(ParticleSystem* particle_system);
private:
    
    // static std::shared_ptr<GraphicsEngine> instance;
    int _window_width;
    int _window_height;
    World* _world;
    BasePlayerCharacter* _player_character;
    std::vector<GameObject*> gameObjects;
    std::vector<Prop*> environmentProps;
    ParticleSystem* _particle_system;
    Camera2D player_camera{Vector2{(float)_window_width/2, (float)_window_height/2}, _player_character->GetWorldPosition(), 0.0, 1.0};
};