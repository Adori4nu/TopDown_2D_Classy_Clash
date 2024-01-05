#include "Game.hpp"

#include "include/raylib.h"

#include "gameConstants.hpp"
#include "GraphicsEngine.hpp"
#include "helperFunctions.hpp"
#include "Random.hpp"

#include <algorithm>
#include <assert.h>
#include <fstream>

#include "BaseEnemy.hpp"
#include "BasePlayerCharacter.hpp"
#include "gameConstants.hpp"
#include "GameObject.hpp"
#include "helperFunctions.hpp"
#include "ParticleSystem.hpp"
#include "Prop.hpp"
#include "Screen.hpp"
#include "World.hpp"


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

World _world{};// GetTexture(TextureIDs::TileSetTexture)
ParticleSystem damage_number_popups{};
std::vector<Prop> environmentProps;
std::vector<GameObject> gameObjects;
std::vector<BaseEnemy> enemiesPool;
// Static Player won't have textures loaded this constructor is garbage because Textures are loaded in initialisation proces
BasePlayerCharacter player_character{ObjectType::Base_Player, window_width, window_height, GetTexture(TextureIDs::Actors::player_idle_texture), GetTexture(TextureIDs::Actors::player_runing_texture), ASSET_SCALE, damage_number_popups};
GameHudScreen game_HUD(player_character);
std::vector<bool> woon;

void InitGame()
{
    auto& Graphics_Engine_ = GraphicsEngine::Get();
    
    _world.SetWorldTexture(GetTexture(TextureIDs::TileSetTexture));
    _world.LoadMap();
    Graphics_Engine_.SetWorldToRender(&_world);
    
    StopBGM();
    // make a function to set bgm volume in helper functions
    // SetMusicVolume(BGM, 0.125f);
    StartBGM(_world.GetBGM_path().c_str());

    Prop rock{ObjectType::Prop, Vector2{9*32.f, 9*32.f}, GetTexture(TextureIDs::Props::rock_texture), 1.f};
    Prop log{ObjectType::Prop, Vector2{13*32.f, 10*32.f}, GetTexture(TextureIDs::Props::log_texture), 2.f};
    Prop cherry{ObjectType::Prop, Vector2{12*32.f, 12*32.f}, GetTexture(TextureIDs::Props::cherry_tree), 4.f};
    
    Prop* props[3]
    {
        &rock
        , &log
        , &cherry
    };

    std::ifstream inFile("../character_data.txt"); // or character_data.txt :thinking:
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
    Graphics_Engine_.SetPlayerToRender(&player_character);
    Graphics_Engine_.SetCameraToRender(&player_character.player_camera);
    
    Actor dummy_NPC{ObjectType::Actor, GetTexture(TextureIDs::Actors::player_idle_texture), Vector2{24*32.f, 24*32.f}, ASSET_SCALE};
    
    dummy_NPC.SetWorld(_world);
    gameObjects.push_back(dummy_NPC);
    Graphics_Engine_.AddGameObject(&gameObjects.back());
    
    EnemyType* nullEnemy{nullptr};

    EnemyType goblin_minion {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::goblin_idle_texture), GetTexture(TextureIDs::Actors::goblin_run_texture), 2.0f, 2.5f, 5, 10};
    EnemyType goblin_small {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::goblin_idle_texture), GetTexture(TextureIDs::Actors::goblin_run_texture), 3.0f, 2.f, 6, 20};
    EnemyType goblin_medium {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::goblin_idle_texture), GetTexture(TextureIDs::Actors::goblin_run_texture), 4.0f, 1.75f, 7, 40};
    EnemyType goblin_boss {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::goblin_idle_texture), GetTexture(TextureIDs::Actors::goblin_run_texture), 6.0f, 1.5f, 10, 80};

    EnemyType slime_minion {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::slime_idle_texture), GetTexture(TextureIDs::Actors::slime_run_texture), 2.0f, 2.5f * 1.5f, 2, 10};
    EnemyType slime_small {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::slime_idle_texture), GetTexture(TextureIDs::Actors::slime_run_texture), 3.0f, 2.f * 1.5f, 2, 20};
    EnemyType slime_medium {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::slime_idle_texture), GetTexture(TextureIDs::Actors::slime_run_texture), 4.0f, 1.75f * 1.5f, 3, 30};
    EnemyType slime_boss {ObjectType::Base_Enemy, nullEnemy, GetTexture(TextureIDs::Actors::slime_idle_texture), GetTexture(TextureIDs::Actors::slime_run_texture), 6.0f, 1.5f * 1.5f, 5, 60};

    BaseEnemy* enemy1 = goblin_minion.newEnemy();
    BaseEnemy* enemy2 = goblin_minion.newEnemy();
    BaseEnemy* enemy3 = goblin_minion.newEnemy();
    BaseEnemy* enemy4 = goblin_minion.newEnemy();
    BaseEnemy* enemy5 = goblin_small.newEnemy();
    BaseEnemy* enemy6 = goblin_medium.newEnemy();
    BaseEnemy* enemy7 = goblin_boss.newEnemy();
    BaseEnemy* enemy8 = slime_minion.newEnemy();
    BaseEnemy* enemy9 = slime_minion.newEnemy();
    BaseEnemy* enemy10 = slime_minion.newEnemy();
    BaseEnemy* enemy11 = slime_minion.newEnemy();
    BaseEnemy* enemy12 = slime_small.newEnemy();
    BaseEnemy* enemy13 = slime_medium.newEnemy();
    BaseEnemy* enemy14 = slime_boss.newEnemy();
    BaseEnemy* enemy15 = slime_small.newEnemy();
    BaseEnemy* enemy16 = slime_medium.newEnemy();


    BaseEnemy* enemies[]
    {
        enemy1
        , enemy2
        , enemy3
        , enemy4
        , enemy5
        , enemy6
        , enemy7
        , enemy8
        , enemy9
        , enemy10
        , enemy11
        , enemy12
        , enemy13
        , enemy14
        , enemy15
        , enemy16
    };

    for (auto prop: props)
    {
        prop->SetWorld(_world);
        environmentProps.push_back(*prop);
        Graphics_Engine_.AddProp(&environmentProps.back());
    }


    for (auto enemy : enemies)
    {
        enemy->SetParticleSystem(damage_number_popups);
        enemy->SetWorld(_world);
        enemy->SetWorldPosition(Vector2{(Random::Int(12,48))*32.f, (Random::Int(12,48))*32.f});
        
        for(auto prop : props)
            while(CheckCollisionRecs(enemy->GetCollisionRectangle(), prop->GetCollisionRectangle()))
            {
                enemy->SetWorldPosition(Vector2{(Random::Int(12,48))*32.f, (Random::Int(12,48))*32.f});
            }
        
        enemy->SetTarget(&player_character);
        enemiesPool.push_back(*enemy);

        Graphics_Engine_.AddGameObject(&enemiesPool.back());
    }

    Graphics_Engine_.SetParticleSystemToRender(&damage_number_popups);

    // woon.resize(std::size(enemiesPool), false);

    SetActiveScreen(&game_HUD);
}

void ActivateGame()
{
    SetActiveScreen(&game_HUD);
}

void UpdateGame(bool& should_stop_playing)
{
    float delta_time{GetFrameTime()};

    if (WindowShouldClose())
    {
        should_stop_playing = true;
        std::ofstream file("../character_data.txt");
        if (file.is_open()) {
            file << player_character;
            file.close();
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }
    // if (std::all_of(woon.cbegin(), woon.cend(), [](bool KO_val) { return KO_val; }))
    // {
    //     BeginDrawing();
    //     DrawText("You Win!", window_width / 2 - MeasureText("You Win!", 40) / 2, window_height / 2 - 40, 40, YELLOW);
    //     EndDrawing();
    //     std::ofstream file("../character_data.txt");
    //     if (file.is_open()) {
    //         file << player_character;
    //         file.close();
    //     } else {
    //         std::cerr << "Unable to open file for writing." << std::endl;
    //     }
    //     WaitTime(3);
    //     // applicationState = AppState::GameOver;
    // }

    player_character.tick(delta_time);
    // if (player_character.GetWorldPosition().x < (0.f - 32.f*3 - 8.f) * ASSET_SCALE ||
    //     player_character.GetWorldPosition().y < (0.f - 32.f*1 - 8.f) * ASSET_SCALE ||
    //     player_character.GetWorldPosition().x + window_width > (map_texture.width + 32.f*4 - 24.f) * ASSET_SCALE ||
    //     player_character.GetWorldPosition().y + window_height > (map_texture.height + 32.f*2 - 24.f) * ASSET_SCALE
    // )
    // {
    //     player_character.UndoMovement();
    // }
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
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
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
    damage_number_popups.tick(delta_time);
}

void QuitGame()
{
    _world.ClearWorld(); // <- World in my case
}

