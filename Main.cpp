#include "include/raylib.h"
#include "include/raymath.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "BasePlayerCharacter.hpp"
#include "BaseEnemy.hpp"
#include "Prop.hpp"
#include "ParticleSystem.hpp"
#include "GameObject.hpp"
#include "GraphicsEngine.hpp"
#include "Random.hpp"
#include "World.hpp"

// constexpr float ASSET_SCALE{4.0f};

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Random::Init();

    const int window_width{1280};
    const int window_height{720};

    InitWindow(window_width, window_height, "Top Down 2D Game");
    
    // Map
    // "textures/tiled_maps/RPG Nature Tileset.png"
    // "textures/tiled_maps/map.png"
    Texture2D map_texture = LoadTexture("textures/tiled_maps/RPG Nature Tileset.png");
    World base_level(map_texture);
    // World* world_ptr = &base_level;

    // Prop
        // Rocks
    Texture2D rock_texture = LoadTexture("textures/tiled_maps/Rock.png");
        // Log
    Texture2D log_texture = LoadTexture("textures/tiled_maps/Log.png");
        // Tree
    Texture2D cherry_tree = LoadTexture("textures/tiled_maps/cherry_tree.png");

    Prop rock{ObjectType::Prop, Vector2{9*32.f, 9*32.f}, rock_texture, 1.f};
    Prop log{ObjectType::Prop, Vector2{13*32.f, 10*32.f}, log_texture, 2.f};
    Prop cherry{ObjectType::Prop, Vector2{12*32.f, 12*32.f}, cherry_tree, 4.f};
    
    Prop* props[3]
    {
        &rock
        , &log
        , &cherry
    };

    // ParticleSystem
    ParticleSystem damage_number_popups;

    // Player
    Texture2D player_idle_texture = LoadTexture("textures/characters/knight_idle_spritesheet.png");
    Texture2D player_runing_texture = LoadTexture("textures/characters/knight_run_spritesheet.png");

    BasePlayerCharacter player{ObjectType::Base_Player, window_width, window_height, player_idle_texture, player_runing_texture, ASSET_SCALE, damage_number_popups};

    Actor dummy_NPC{ObjectType::Actor, player_idle_texture, Vector2{24*32.f, 24*32.f}, ASSET_SCALE};

    std::ifstream inFile("character_data.txt");
    if (inFile.is_open()) {
        inFile >> player;
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for Reading." << std::endl;
        player.PostInitConstruct(Vector2{4*32.f, 4*32.f});
    }

    // Enemy
        // Goblin
    Texture2D goblin_idle_texture = LoadTexture("textures/characters/goblin_idle_spritesheet.png");
    Texture2D goblin_run_texture = LoadTexture("textures/characters/goblin_run_spritesheet.png");

    EnemyType* nullEnemy{nullptr};

    EnemyType goblin_minion {ObjectType::Base_Enemy, nullEnemy, goblin_idle_texture, goblin_run_texture, 2.0f, 2.5f, 5, 10};
    EnemyType goblin_small {ObjectType::Base_Enemy, nullEnemy, goblin_idle_texture, goblin_run_texture, 3.0f, 2.f, 6, 20};
    EnemyType goblin_medium {ObjectType::Base_Enemy, nullEnemy, goblin_idle_texture, goblin_run_texture, 4.0f, 1.75f, 7, 40};
    EnemyType goblin_boss {ObjectType::Base_Enemy, nullEnemy, goblin_idle_texture, goblin_run_texture, 6.0f, 1.5f, 10, 80};

        // Slime
    Texture2D slime_idle_texture = LoadTexture("textures/characters/slime_idle_spritesheet.png");
    Texture2D slime_run_texture = LoadTexture("textures/characters/slime_run_spritesheet.png");

    EnemyType slime_minion {ObjectType::Base_Enemy, nullEnemy, slime_idle_texture, slime_run_texture, 2.0f, 2.5f * 1.5f, 2, 10};
    EnemyType slime_small {ObjectType::Base_Enemy, nullEnemy, slime_idle_texture, slime_run_texture, 3.0f, 2.f * 1.5f, 2, 20};
    EnemyType slime_medium {ObjectType::Base_Enemy, nullEnemy, slime_idle_texture, slime_run_texture, 4.0f, 1.75f * 1.5f, 3, 30};
    EnemyType slime_boss {ObjectType::Base_Enemy, nullEnemy, slime_idle_texture, slime_run_texture, 6.0f, 1.5f * 1.5f, 5, 60};

    // Asocjacja (Agregacja) - zachodzi pomiędzy Enemy Type, a Base Enemy
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

    GraphicsEngine Graphics_Engine_(window_width
                                    , window_height
                                    , &base_level
                                    , &player
                                    , &damage_number_popups);
    
    for (auto prop: props)
    {
        Graphics_Engine_.AddProp(prop);
    }

    for (auto enemy : enemies)
    {
        enemy->SetParticleSystem(damage_number_popups);
        enemy->SetWorldPosition(Vector2{(Random::Int(12,48))*32.f, (Random::Int(12,48))*32.f});
        
        // while (CheckCollisionRecs(enemy->GetCollisionRectangle(), prop->GetCollisionRectangle()))
        for(auto prop : props)
            while(CheckCollisionRecs(enemy->GetCollisionRectangle(), prop->GetCollisionRectangle()))
            {
                enemy->SetWorldPosition(Vector2{(Random::Int(12,48))*32.f, (Random::Int(12,48))*32.f});
            }
        
        enemy->SetTarget(&player);
        Graphics_Engine_.AddGameObject(enemy);
    }

    Graphics_Engine_.AddGameObject(&dummy_NPC);

    // Zaimplementować pattern Dirty Flag, Type Object - done
    // , Object Pool, Flyweight, Component

    std::array<bool, std::size(enemies)> woon{false};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    bool stop_playing{false};
    // Main game loop
    while (!stop_playing)    // Detect window close button or ESC key
    {
        float delta_time{GetFrameTime()};
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        for (size_t i = 0; i < std::size(enemies); i++)
            (!enemies[i]->IsAlive()) ? woon[i] = true : woon[i] = false;

        if (WindowShouldClose())
        {
            stop_playing = true;
            std::ofstream file("character_data.txt");
            if (file.is_open()) {
                file << player;
                file.close();
            } else {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
        }

        player.tick(delta_time);
        // if (player.GetWorldPosition().x < (0.f - 32.f*3 - 8.f) * ASSET_SCALE ||
        //     player.GetWorldPosition().y < (0.f - 32.f*1 - 8.f) * ASSET_SCALE ||
        //     player.GetWorldPosition().x + window_width > (map_texture.width + 32.f*4 - 24.f) * ASSET_SCALE ||
        //     player.GetWorldPosition().y + window_height > (map_texture.height + 32.f*2 - 24.f) * ASSET_SCALE
        // )
        // {
        //     player.UndoMovement();
        // }
        for (auto prop : props)
        {
            if (CheckCollisionRecs(player.GetCollisionRectangle(), prop->GetCollisionRectangle()))
            {
                player.UndoMovement();
            }
            for (auto enemy : enemies)
                if (CheckCollisionRecs(enemy->GetCollisionRectangle(), prop->GetCollisionRectangle()))
                    enemy->UndoMovement();
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(player.GetWeaponCollisionRectangle(), enemy->GetCollisionRectangle()) && enemy->IsAlive())
                {
                    if(Random::Float(1,100) < 90)
                    {
                        player.IncreaseKillCount(enemy->TakeDamage(player.GetDamage()));
                        player.SetParticleToEmitType(Type::ENEMY_HIT);
                        player.SetParticleToEmitPosition({enemy->GetWorldPosition().x + 6*4.f, enemy->GetWorldPosition().y - 6 * 4.f});
                        damage_number_popups.Emit(player.GetParticleToEmit());
                    }
                    else
                    {
                        player.SetParticleToEmitType(Type::DODGE);
                        player.SetParticleToEmitPosition({enemy->GetWorldPosition().x + 6*4.f, enemy->GetWorldPosition().y - 6 * 4.f});
                        damage_number_popups.Emit(player.GetParticleToEmit());
                    }
                }
            }
        };
        for (auto enemy : enemies)
        {
            enemy->tick(delta_time);
        }
        damage_number_popups.tick(delta_time);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        

        Graphics_Engine_.RenderAll();
        if (std::all_of(woon.cbegin(), woon.cend(), [](bool KO_val) { return KO_val; }))
        {
            BeginDrawing();
            DrawText("You Win!", window_width / 2 - MeasureText("You Win!", 40) / 2, window_height / 2 - 40, 40, YELLOW);
            EndDrawing();
            std::ofstream file("character_data.txt");
            if (file.is_open()) {
                file << player;
                file.close();
            } else {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
            WaitTime(3);
            break;
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(map_texture);     // Unload map texture
    UnloadTexture(rock_texture);    // Unload rock texture
    UnloadTexture(log_texture);     // Unload log texture
    UnloadTexture(cherry_tree);     // Unload cherry tree texture
    UnloadTexture(goblin_idle_texture);     // Unload goblin idle texture
    UnloadTexture(goblin_run_texture);     // Unload goblin run texture
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}