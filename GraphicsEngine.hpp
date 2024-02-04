#pragma once

#include "include/raylib.h"
#include "include/raymath.h"

#include <memory>
#include <vector>

#include "appState.hpp"
#include "BasePlayerCharacter.hpp"
#include "gameConstants.hpp"

// class Actor;
class BaseEnemy;
// class BasePlayerCharacter;
class GameObject;
// class Pawn;
class Prop;
class World;
class Screen;

class GraphicsEngine
{
private:
GraphicsEngine(){};
    // GraphicsEngine(int window_width
    //             , int window_height
    //             , World* world
    //             , BasePlayerCharacter* player
    //             , ParticleSystem* particle_system)
    //             : _window_width(window_width)
    //             , _window_height(window_height)
    //             , _world(world)
    //             , _player_character(player)
    //             , damage_number_popups(particle_system)
    //             {
    //                 // gameObjects.resize(100);
    //                 // environmentProps.resize(100);
    //             };
                
    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;
public:
    // static std::shared_ptr<GraphicsEngine> GetInstance() {
    //     if(!instance)
    //         instance = std::make_shared<GraphicsEngine>();
    //     return instance;
    // }

    // static void Initialize(Texture2D& world, BasePlayerCharacter& player)
    // {
    //     instance = std::make_shared<GraphicsEngine>();
    // };
    static GraphicsEngine& Get()
    {
        return s_Instance;
    }

    void AddGameObject(GameObject* gameObject) {
        gameObjects.push_back(gameObject);
    }
    void AddProp(Prop* gameObject) {
        environmentProps.push_back(gameObject);
    }

    void SetWorldToRender(World* world_to_render) { _world = world_to_render; };
    void SetPlayerToRender(BasePlayerCharacter* player_character) { _player_character = player_character; };
    void SetParticleSystemToRender(ParticleSystem* damage_number_popups) { _damage_number_popups = damage_number_popups; };
    void SetCameraToRender(Camera2D* camera) { _player_camera = camera; }
    void SetScreenToRender(Screen* screen_to_render) { active_screen = screen_to_render; };

    void RenderAll(AppState app_state);

private:

    void RenderWorld(World* world);

    void Render(Prop* prop);

    void Render(Actor* actor);

    void Render(Pawn* pawn);

    void Render(BaseEnemy* enemy);

    void Render(BasePlayerCharacter* player);

    void Render(ParticleSystem* particle_system);

    void RenderGameClock(float game_clock);

    static GraphicsEngine s_Instance;

    int _window_width{window_width};
    int _window_height{window_height};
    World* _world;
    BasePlayerCharacter* _player_character;
    std::vector<GameObject*> gameObjects;
    std::vector<Prop*> environmentProps;
    std::vector<BaseEnemy*> enemies_to_render;
    ParticleSystem* _damage_number_popups;
    Camera2D* _player_camera;
    Screen* active_screen;
};