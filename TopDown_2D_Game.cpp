#include <raylib.h>
#include <raymath.h>
#include <string>

#include "Character.hpp"
#include "Enemy.hpp"
#include "Prop.hpp"

#define ASSET_SCALE 4.0f

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int window_width{384};
    const int window_height{384};

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

    // Player
    Texture2D player_idle_texture = LoadTexture("textures/characters/knight_idle_spritesheet.png");
    Texture2D player_runing_texture = LoadTexture("textures/characters/knight_run_spritesheet.png");
    Character player{window_width, window_height, player_idle_texture, player_runing_texture, Vector2{0.f, 0.f}, 4.f};

    // Enemy
    Texture2D goblin_idle_texture = LoadTexture("textures/characters/goblin_idle_spritesheet.png");
    Texture2D goblin_run_texture = LoadTexture("textures/characters/goblin_run_spritesheet.png");

    Enemy enemies[4]
    {
        Enemy {goblin_idle_texture, goblin_run_texture, Vector2{7*32.f, 7*32.f}, 2.0f, 2.5f, 5.f},
        Enemy {goblin_idle_texture, goblin_run_texture, Vector2{8*32.f, 8*32.f}, 3.0f, 2.f, 6.5f},
        Enemy {goblin_idle_texture, goblin_run_texture, Vector2{12*32.f, 12*32.f}, 4.0f, 1.75f, 7.25f},
        Enemy {goblin_idle_texture, goblin_run_texture, Vector2{9*32.f, 9*32.f}, 6.0f, 1.5f, 10.f},
    };

    for (auto& enemy : enemies)
    {
        enemy.SetTarget(&player);
    }

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta_time{GetFrameTime()};
        // Update
        //----------------------------------------------------------------------------------
        

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
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
            player_health.append(std::to_string(player.GetHealth()), 0, 5);
            DrawText(player_health.c_str(), 55, 45, 40, RED);
        }

        // Draw player character
        player.tick(delta_time);
        if (player.GetWorldPosition().x < 0.f ||
            player.GetWorldPosition().y < 0.f ||
            player.GetWorldPosition().x + window_width > map_texture.width * ASSET_SCALE ||
            player.GetWorldPosition().y + window_height > map_texture.height * ASSET_SCALE
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
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto& enemy : enemies)
            {
                if (CheckCollisionRecs(player.GetWeaponCollisionRectangle(), enemy.GetCollisionRectangle()))
                {
                    enemy.SetIsAlive(false);
                }
            }
        };
        for (auto& enemy : enemies)
        {
            enemy.tick(delta_time);
        }

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