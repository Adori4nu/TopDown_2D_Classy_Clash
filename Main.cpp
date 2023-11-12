#include "include/raylib.h"
#include "include/raymath.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "Character.hpp"
#include "Enemy.hpp"
#include "Prop.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"

#define ASSET_SCALE 4.0f

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Random::Init();

    const int window_width{1280};
    const int window_height{720};

    InitWindow(window_width, window_height, "Top Down 2D Game");
    
    // Map
    Texture2D map_texture = LoadTexture("textures/tiled_maps/map.png");
    Vector2 map_pos{0.0f, 0.0f};

    // Prop
        // Gruz
    Texture2D rock_texture = LoadTexture("textures/tiled_maps/Rock.png");
        // Log
    Texture2D log_texture = LoadTexture("textures/tiled_maps/Log.png");

    Prop props[2]
    {
        Prop{Vector2{9*32.f, 9*32.f}, rock_texture, 1.f},
        Prop{Vector2{15*32.f, 15*32.f}, log_texture, 2.f},
    };

    //ParticleSystem
    ParticleSystem damage_number_popups;

    // Player
    Texture2D player_idle_texture = LoadTexture("textures/characters/knight_idle_spritesheet.png");
    Texture2D player_runing_texture = LoadTexture("textures/characters/knight_run_spritesheet.png");

    Character player{window_width, window_height, player_idle_texture, player_runing_texture, ASSET_SCALE, damage_number_popups};

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

    Enemy goblin_minion {goblin_idle_texture, goblin_run_texture, Vector2{16*32.f, 16*32.f}, 2.0f, 2.5f, 5, 10, damage_number_popups};
    Enemy goblin_small {goblin_idle_texture, goblin_run_texture, Vector2{24*32.f, 24*32.f}, 3.0f, 2.f, 6, 20, damage_number_popups};
    Enemy goblin_medium {goblin_idle_texture, goblin_run_texture, Vector2{12*32.f, 12*32.f}, 4.0f, 1.75f, 7, 40, damage_number_popups};
    Enemy goblin_boss {goblin_idle_texture, goblin_run_texture, Vector2{48*32.f, 48*32.f}, 6.0f, 1.5f, 10, 80, damage_number_popups};

        // Slime
    Texture2D slime_idle_texture = LoadTexture("textures/characters/slime_idle_spritesheet.png");
    Texture2D slime_run_texture = LoadTexture("textures/characters/slime_run_spritesheet.png");

    Enemy slime_minion {slime_idle_texture, slime_run_texture, Vector2{13*32.f, 13*32.f}, 2.0f, 2.5f * 1.5f, 2, 10, damage_number_popups};
    Enemy slime_small {slime_idle_texture, slime_run_texture, Vector2{27*32.f, 27*32.f}, 3.0f, 2.f * 1.5f, 2, 20, damage_number_popups};
    Enemy slime_medium {slime_idle_texture, slime_run_texture, Vector2{42*32.f, 42*32.f}, 4.0f, 1.75f * 1.5f, 3, 30, damage_number_popups};
    Enemy slime_boss {slime_idle_texture, slime_run_texture, Vector2{36*32.f, 36*32.f}, 6.0f, 1.5f * 1.5f, 5, 60, damage_number_popups};

    Enemy* enemies[]
    {
        &goblin_minion,
        &goblin_small,
        &goblin_medium,
        &goblin_boss,
        &slime_minion,
        &slime_small,
        &slime_medium,
        &slime_boss
    };

    for (auto enemy : enemies)
    {
        enemy->SetTarget(&player);
    }

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
                file << player; // Using the serialization operator
                file.close();
            } else {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


        ClearBackground(Color{99, 155, 255, 255});
        map_pos = Vector2Scale(player.GetWorldPosition(), -1.f);
        // Draw the map
        DrawTextureEx(map_texture, map_pos, 0, ASSET_SCALE, WHITE);

        // Draw props
        for (auto& prop : props)
        {
            prop.Render(player.GetWorldPosition());
        }

        if (!player.IsAlive())
        {
            DrawText("Game Over!", window_width / 2 - MeasureText("Game Over!", 40) / 2, window_height / 2 - 40, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string player_health{"Health: "};
            player_health.append(std::to_string(player.GetHealth()), 0, 3);
            DrawText(player_health.c_str(), 55, 45, 40, RED);
            std::string player_kills{"Kill count: "};
            player_kills.append(std::to_string(player.GetKillCount()), 0, 5);
            DrawText(player_kills.c_str(), 55, 100, 30, BLACK);
        }
        if (std::all_of(woon.cbegin(), woon.cend(), [](bool KO_val) { return KO_val; }))
        {
            DrawText("You Win!", window_width / 2 - MeasureText("You Win!", 40) / 2, window_height / 2 - 40, 40, YELLOW);
            EndDrawing();
            std::ofstream file("character_data.txt");
            if (file.is_open()) {
                file << player; // Using the serialization operator
                file.close();
            } else {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
            continue;
        }

        // Draw player character
        player.tick(delta_time);
        if (player.GetWorldPosition().x < (0.f - 32.f*3 - 8.f) * ASSET_SCALE ||
            player.GetWorldPosition().y < (0.f - 32.f*1 - 8.f) * ASSET_SCALE ||
            player.GetWorldPosition().x + window_width > (map_texture.width + 32.f*4 - 24.f) * ASSET_SCALE ||
            player.GetWorldPosition().y + window_height > (map_texture.height + 32.f*2 - 24.f) * ASSET_SCALE
        )
        {
            player.UndoMovement();
        }
        for (auto& prop : props)
        {
            if (CheckCollisionRecs(player.GetCollisionRectangle(), prop.GetCollisionRectangle(player.GetWorldPosition())))
            {
                player.UndoMovement();
            }
            for (auto enemy : enemies)
                if (CheckCollisionRecs(enemy->GetCollisionRectangle(), prop.GetCollisionRectangle(player.GetWorldPosition())))
                    enemy->UndoMovement();
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(player.GetWeaponCollisionRectangle(), enemy->GetCollisionRectangle()) && enemy->IsAlive())
                {
                    player.IncreaseKillCount(enemy->TakeDamage(player.GetDamage()));
                    player.SetParticleToEmitType(Type::ENEMY_HIT);
                    player.SetParticleToEmitPosition({enemy->GetScreenPosition().x + 6*4.f, enemy->GetScreenPosition().y - 6 * 4.f});
                    damage_number_popups.Emit(player.GetParticleToEmit());
                }
            }
        };
        for (auto enemy : enemies)
        {
            enemy->tick(delta_time);
        }
        damage_number_popups.tick(delta_time);

        DrawFPS(window_width - 60, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(map_texture);     // Unload map texture
    UnloadTexture(rock_texture);    // Unload rock texture
    UnloadTexture(log_texture);     // Unload log texture
    UnloadTexture(goblin_idle_texture);     // Unload goblin idle texture
    UnloadTexture(goblin_run_texture);     // Unload goblin run texture
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}