#pragma once

constexpr int window_width{1280};
constexpr int window_height{720};

namespace TextureIDs
{
    // Texture IDs
    constexpr int TileSetTexture = 0;

    namespace Props
    {
        constexpr int rock_texture = 1;
        constexpr int log_texture = 2;
        constexpr int cherry_tree = 3;
    }

    namespace Actors
    {
        constexpr int player_idle_texture = 4;
        constexpr int player_runing_texture = 5;
        constexpr int goblin_idle_texture = 6;
        constexpr int goblin_run_texture = 7;
        constexpr int slime_idle_texture = 8;
        constexpr int slime_run_texture = 9;
    }

    namespace Equipment
    {
        constexpr int basic_sword_texture = 10;
    }

    namespace SpriteIDs
    {
        namespace Map
        {
            
        }
        
        namespace UI
        {
            constexpr int inventory_sprite = 11;
            constexpr int equipment_sprite = 12;
        }

        namespace Equipment
        {

        }

    }
}
namespace SoundIds
{
    namespace music
    {

    }
    namespace sfx
    {
        constexpr int HoveredSound = 0;
        constexpr int ClickSound = 1;
    }
}