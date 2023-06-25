#include <raylib.h>
#include <raymath.h>


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth{384};
    const int screenHeight{384};

    InitWindow(screenWidth, screenHeight, "Top Down 2D Game");
    
    Texture2D map_texture = LoadTexture("textures/tiled_maps/map.png");
    Vector2 map_pos{0.0f, 0.0f};
    float speed{4.0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // float delta_time{GetFrameTime()};
        // Update
        //----------------------------------------------------------------------------------
        Vector2 direction{};
        if (IsKeyDown(KEY_A))
        {
            direction.x -= 1.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            direction.x += 1.0f;
        }
        if (IsKeyDown(KEY_W))
        {
            direction.y -= 1.0f;
        }
        if (IsKeyDown(KEY_S))
        {
            direction.y += 1.0f;
        }
        if (Vector2Length(direction) != 0)
        {
            Vector2Normalize(direction);
            // set map_pos = map_pos - direction
            map_pos = Vector2Subtract(map_pos, Vector2Scale(direction, speed));
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureEx(map_texture, map_pos, 0, 4.0f, WHITE);

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