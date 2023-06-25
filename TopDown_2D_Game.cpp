#include <raylib.h>
#include <raymath.h>

#define ASET_SCALE 4.0f

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
    float speed{4.0};

    // Player
    Texture2D player_idle_texture = LoadTexture("textures/characters/knight_idle_spritesheet.png");
    Texture2D player_runing_texture = LoadTexture("texture/characters/knight_run_spritesheet.png");
    Vector2 player_pos
    {
        window_width / 2.0f - ASET_SCALE * (0.5f * player_idle_texture.width / 6.0f),
        window_height / 2.0f - ASET_SCALE * (0.5f * player_idle_texture.height)
    };
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

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
            // Set map_pos = map_pos - direction
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the map
        DrawTextureEx(map_texture, map_pos, 0, ASET_SCALE, WHITE);

        // Draw player character
        Rectangle player_source{0.f, 0.f, rightLeft * (float)player_idle_texture.width / 6.f, (float)player_idle_texture.height};
        Rectangle player_dest{player_pos.x, player_pos.y, ASET_SCALE * (float)player_idle_texture.width / 6.f, ASET_SCALE * (float)player_idle_texture.height};
        DrawTexturePro(player_idle_texture, player_source, player_dest, Vector2{}, 0.f, WHITE);

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