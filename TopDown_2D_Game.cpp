#include <raylib.h>


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth{384};
    const int screenHeight{384};

    InitWindow(screenWidth, screenHeight, "Top Down 2D Game");
    
    Texture2D map_texture = LoadTexture("textures/tiled_maps/map.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureEx(map_texture, (Vector2){0, 0}, 0, 4.0f, WHITE);

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