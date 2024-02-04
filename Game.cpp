#include "Game.hpp"

#include "include/raylib.h"

#include "BaseEnemy.hpp"
#include "BasePlayerCharacter.hpp"
#include "EnemySpawner.hpp"
#include "gameConstants.hpp"
#include "GameObject.hpp"
#include "GraphicsEngine.hpp"
#include "helperFunctions.hpp"
#include "ParticleSystem.hpp"
#include "Prop.hpp"
#include "Random.hpp"
#include "Screen.hpp"
#include "World.hpp"

#include <algorithm>
#include <assert.h>
#include <fstream>

// int width, int height, int target_framerate, std::string game_title
// Game::Game()
// {
//     // assert(GetWindowHandle());
//     // InitWindow(width, height, game_title.c_str());
// }

// Game::~Game() noexcept
// {
//     // assert(GetWindowHandle());
//     // CloseWindow();
// }

// void Game::Tick()
// {
    
// }

// void Game::Init()
// {

// }

// void Game::Update()
// {
    
// }

World _world{};
ParticleSystem damage_number_popups{};
std::vector<Prop> environmentProps{};
std::vector<GameObject> gameObjects{};
std::vector<Actor> gameActors{};
std::vector<BaseEnemy> enemiesPool{};
BasePlayerCharacter player_character{ObjectType::Base_Player, window_width, window_height, TextureIDs::Actors::player_idle_texture, TextureIDs::Actors::player_runing_texture, ASSET_SCALE, damage_number_popups};
GameHudScreen game_HUD(player_character);
EnemySpawner mob_spawner{};
SceneType scene_type{SceneType::SURVIVAL_MODE};

float game_clock{};

void InitGame()
{
    environmentProps.reserve(128);
    gameObjects.reserve(128);
    gameActors.reserve(128);
    enemiesPool.reserve(128);

    auto& Graphics_Engine_ = GraphicsEngine::Get();
    
    _world.SetWorldTexture(GetTexture(TextureIDs::TileSetTexture));
    _world.LoadMap();
    Graphics_Engine_.SetWorldToRender(&_world);
    
    StopBGM();
    StartBGM(_world.GetBGM_path().c_str());
    SetMusicVolume(GetBGM(), 0.125f);

    Prop rock{ObjectType::Prop, Vector2{9*32.f, 9*32.f}, TextureIDs::Props::rock_texture, 1.f};
    Prop log{ObjectType::Prop, Vector2{13*32.f, 10*32.f}, TextureIDs::Props::log_texture, 2.f};
    Prop cherry{ObjectType::Prop, Vector2{12*32.f, 12*32.f}, TextureIDs::Props::cherry_tree, 4.f};
    
    Prop* props[3]
    {
        &rock
        , &log
        , &cherry
    };

    std::ifstream inFile("../character_data.txt");
    if (inFile.is_open()) {
        inFile >> player_character;
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for Reading." << std::endl;
        player_character.PostInitConstruct(Vector2{4*32.f, 4*32.f});
    }
    player_character.SetWeaponTexture(GetTexture(TextureIDs::Equipment::basic_sword_texture));
    player_character.SetWorld(_world);
    player_character.SetWidthAndHeight();
    Graphics_Engine_.SetPlayerToRender(&player_character);
    Graphics_Engine_.SetCameraToRender(&player_character.player_camera);
    
    Actor dummy_NPC{ObjectType::Actor, TextureIDs::Actors::player_idle_texture, Vector2{24*32.f, 24*32.f}, ASSET_SCALE};
    
    dummy_NPC.SetWorld(_world);
    dummy_NPC.SetWidthAndHeight();
    gameActors.emplace_back(dummy_NPC);
    Graphics_Engine_.AddGameObject(&gameActors.back());
    
    EnemyType* nullEnemy{nullptr};

    EnemyType goblin_minion {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::goblin_idle_texture, TextureIDs::Actors::goblin_run_texture, 2.0f, 2.5f, 5, 10};
    EnemyType goblin_small {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::goblin_idle_texture, TextureIDs::Actors::goblin_run_texture, 3.0f, 2.f, 6, 40};
    EnemyType goblin_medium {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::goblin_idle_texture, TextureIDs::Actors::goblin_run_texture, 4.0f, 1.75f, 7, 80};
    EnemyType goblin_boss {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::goblin_idle_texture, TextureIDs::Actors::goblin_run_texture, 10.0f, 1.5f, 10, 160};

    EnemyType slime_minion {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::slime_idle_texture, TextureIDs::Actors::slime_run_texture, 2.0f, 2.5f * 1.5f, 2, 10};
    EnemyType slime_small {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::slime_idle_texture, TextureIDs::Actors::slime_run_texture, 3.0f, 2.f * 1.5f, 2, 30};
    EnemyType slime_medium {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::slime_idle_texture, TextureIDs::Actors::slime_run_texture, 4.0f, 1.75f * 1.5f, 3, 50};
    EnemyType slime_boss {ObjectType::Base_Enemy, nullEnemy, TextureIDs::Actors::slime_idle_texture, TextureIDs::Actors::slime_run_texture, 6.0f, 1.5f * 1.5f, 5, 120};

    for (auto prop: props)
    {
        prop->SetWorld(_world);
        // prop->SetWidthAndHeight();
        environmentProps.emplace_back(*prop);
        Graphics_Engine_.AddProp(&environmentProps.back());
    }

    // mob_spawner.AddWave(EnemyWave{0, 20, goblin_minion, 16, 1.f, 0.f});
    // mob_spawner.AddWave(EnemyWave{20, 40, goblin_small, 8, 2.f, 0.f});
    // mob_spawner.AddWave(EnemyWave{0, 60, goblin_medium, 3, 20.f, 0.f,});
    mob_spawner.AddWave(EnemyWave{30, 30, goblin_boss, 6, 20.f, 0.f,});
    
    mob_spawner.AddWave(EnemyWave{0, 30, slime_minion, 120, 0.25f, 0.f,});
    // mob_spawner.AddWave(EnemyWave{10, 10, slime_minion, 3, 20.f, 0.f,});
    // mob_spawner.AddWave(EnemyWave{10, 10, slime_minion, 3, 20.f, 0.f,});
    // mob_spawner.AddWave(EnemyWave{10, 10, slime_minion, 3, 20.f, 0.f,});

    Graphics_Engine_.SetParticleSystemToRender(&damage_number_popups);

    SetActiveScreen(&game_HUD);
}

void ActivateGame()
{
    SetActiveScreen(&game_HUD);
}

void UpdateGame(AppState& game_state)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        if (game_HUD.InventoryOpen || game_HUD.EquipmentOpen)
        {
            game_HUD.InventoryOpen = false;
            game_HUD.EquipmentOpen = false;
        }
        else
        {
            PauseGame();
            return;
        }
    }

    float delta_time{GetFrameTime()};

    game_clock += delta_time;

    player_character.tick(delta_time);

    for (auto& prop : environmentProps)
    {
        if (CheckCollisionRecs(player_character.GetCollisionRectangle(), prop.GetCollisionRectangle()))
        {
            player_character.UndoMovement();
        }
        for (auto& enemy : enemiesPool)
            if (CheckCollisionRecs(enemy.GetCollisionRectangle(), prop.GetCollisionRectangle()))
                enemy.UndoMovement();
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        for (auto& enemy : enemiesPool)
        {                                                                                                           // enemy._healthComponent.is_alive
            if (CheckCollisionRecs(player_character.GetWeaponCollisionRectangle(), enemy.GetCollisionRectangle()) && enemy.GetHealthComponent().is_alive)
            {
                if(Random::Float(1,100) < 90)
                {                                           //_healthComponent
                    player_character.IncreaseKillCount(enemy.GetHealthComponent().TakeDamage(player_character.GetDamage()));
                    player_character.SetParticleToEmitType(Type::ENEMY_HIT);
                    player_character.SetParticleToEmitPosition({enemy.GetEnemyCenter().x, enemy.GetWorldPosition().y - 32 * 4.f});
                    damage_number_popups.Emit(player_character.GetParticleToEmit());
                }
                else
                {
                    player_character.SetParticleToEmitType(Type::DODGE);
                    player_character.SetParticleToEmitPosition({enemy.GetEnemyCenter().x, enemy.GetWorldPosition().y - 32 * 4.f});
                    damage_number_popups.Emit(player_character.GetParticleToEmit());
                }
            }
        }
    };
    for (auto& enemy : enemiesPool)
    {
        enemy.tick(delta_time);
    }
    for (auto& actor : gameActors)
    {
        actor.tick(delta_time);
    }
    damage_number_popups.tick(delta_time);
    mob_spawner.tick(delta_time);

    if (WindowShouldClose())
    {
        game_state = AppState::Quitting;
        QuitGame();
    }
}

void QuitGame()
{
    _world.ClearWorld();
}

float GetGameClock()
{
    return game_clock;
}

std::vector<BaseEnemy>& GetEnemyPool()
{
    return enemiesPool;
}

BasePlayerCharacter& GetPlayerCharacter()
{
    return player_character;
}

World& GetWorld()
{
    return _world;
}

ParticleSystem& GetParticleSystem()
{
    return damage_number_popups;
}

SceneType GetSceneType()
{
    return scene_type;
}
