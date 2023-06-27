#include <raylib.h>
#include <raymath.h>

#include "Prop.hpp"
#include "Character.hpp"

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
        Prop{Vector2{12*32.f, 12*32.f}, log_texture, 2.f},
    };

    // Player
    Character player{window_width, window_height};

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

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(map_texture);     // Unload map texture
    UnloadTexture(rock_texture);    // Unload rock texture
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}