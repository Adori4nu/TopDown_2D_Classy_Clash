#include <raylib.h>
#include <raymath.h>

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

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(map_texture);     // Unload map texture
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}