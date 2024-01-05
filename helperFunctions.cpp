#include "helperFunctions.hpp"
#include "gameConstants.hpp"
#include "Main.hpp"
#include "Screen.hpp"

#include <deque>
#include <string>
#include <vector>

LoadingScreen* loading_screen{};

std::deque<std::string> textures_to_load{};
std::deque<std::string> sounds_to_load{};

std::vector<Texture> loaded_textures{};

Texture _default_texture{};

size_t _loaded_items{};
size_t _total_to_load{};

Music BGM{0};
std::vector<Sound> sounds{};

struct SpriteInfo
{
    int TextureId{ -1 };
    Rectangle SourceRect{ 0,0,0,0 };
    Vector2 Origin{ 0,0 };

    Rectangle Borders{ 0,0,0,0 };
};

std::vector<SpriteInfo> _sprites_info{};

void InitResources()
{
    loading_screen = new LoadingScreen();
    SetActiveScreen(loading_screen);

    // setup the assets to load
    // textures_to_load.emplace_back(); // logo texture
    textures_to_load.emplace_back("textures/tiled_maps/RPG Nature Tileset.png");
    textures_to_load.emplace_back("textures/tiled_maps/Rock.png");
    textures_to_load.emplace_back("textures/tiled_maps/Log.png");
    textures_to_load.emplace_back("textures/tiled_maps/cherry_tree.png");
    textures_to_load.emplace_back("textures/characters/knight_idle_spritesheet.png");
    textures_to_load.emplace_back("textures/characters/knight_run_spritesheet.png");
    textures_to_load.emplace_back("textures/characters/goblin_idle_spritesheet.png");
    textures_to_load.emplace_back("textures/characters/goblin_run_spritesheet.png");
    textures_to_load.emplace_back("textures/characters/slime_idle_spritesheet.png");
    textures_to_load.emplace_back("textures/characters/slime_run_spritesheet.png");
    textures_to_load.emplace_back("textures/characters/weapon_sword.png");

    // setup default texture
    Image checkered_texture = GenImageChecked(32, 32, 8, 8, PINK, RAYWHITE);
    _default_texture = LoadTextureFromImage(checkered_texture);
    UnloadImage(checkered_texture);

    sounds_to_load.emplace_back("sounds/hover.ogg");
    sounds_to_load.emplace_back("sounds/mouseclick.ogg");
    // sounds_to_load.emplace_back("sounds/click.xxx");

    _total_to_load = textures_to_load.size() + sounds_to_load.size();
}

void InitAudio()
{
    InitAudioDevice();
    SetMasterVolume(0.25f);
    StartBGM("sounds/marvin03 brigth.ogg"); // change path
}

int LoadSoundFile(const char* sound_file)
{
    sounds.push_back(LoadSound(sound_file));
    return int(sounds.size() - 1);
}

void UpdateLoad()
{
    if (textures_to_load.empty() && sounds_to_load.empty())
    {
        FinalizeLoad();
        LoadComplete();
        return;
    }

    constexpr int max_resources_per_frame{ 1 };

    for (int i = 0; i < max_resources_per_frame; i++)
    {
        if (!textures_to_load.empty())
        {
            loaded_textures.push_back(LoadTexture(textures_to_load.front().c_str()));
            textures_to_load.pop_front();

            _loaded_items++;
        }
        else if (!sounds_to_load.empty())
        {
            LoadSoundFile(sounds_to_load.front().c_str());
            sounds_to_load.pop_front();
            _loaded_items++;
        }
    }

    loading_screen->load_proggres = _loaded_items/float(_total_to_load);
}

void UpdateAudio()
{
    if (BGM.frameCount > 0)
        UpdateMusicStream(BGM);
}

void FinalizeLoad()
{
    LoadSpriteFrames(TextureIDs::TileSetTexture, 14, 12, 0);

    for (int i = 0; i < 14; i++)
    {
        // CenterSprite(i);
        // CenterSprite(i + 14);
    }

    // CenterSprite(PlayerSprite);

    // CenterSprite(xyzSprite);

    // SetSpriteBorders(InventoryBackgroundSprite, 10);
    // SetSpriteBorders(ItemBackgroundSprite, 10);

    // SetupDefaultItems();
    // SetupDefaultMobs();
}

void PlaySound(int sound)
{
    if (sound < 0 || sound > sounds.size())
        return;
    
    PlaySound(sounds[sound]);
}

void StartBGM(const char* music_file)
{
    StopBGM();
    BGM = LoadMusicStream(music_file);
    BGM.looping = true;
    PlayMusicStream(BGM);
}

void StopBGM()
{
    if (BGM.frameCount > 0)
    {
        StopMusicStream(BGM);
        UnloadMusicStream(BGM);
        BGM.frameCount = 0;
    }
}

void ShutdownAudio()
{
    CloseAudioDevice();
    for (const auto& sound : sounds)
        UnloadSound(sound);
    
    sounds.clear();
    StopBGM();
}

void CleanupResources()
{
    // free the loading screen ptr
    if (loading_screen)
        delete(loading_screen);

    // unload the textures
    UnloadTexture(_default_texture);
    for (const Texture& texture : loaded_textures)
        UnloadTexture(texture);

    // clear all the stored data
    loaded_textures.clear();
    _default_texture.id = 0;
    loading_screen = nullptr;
}

Texture& GetTexture(int id)
{
    if (id < 0 || id > int(loaded_textures.size()))
        return _default_texture;

    return loaded_textures[id];
}

void LoadSpriteFrames(int texture_id, int columns, int rows, int spacing)
{
    if ( columns == 0 || rows == 0)
        return;

    const Texture2D& texture = GetTexture(texture_id);

    int item_width = (texture.width + spacing) / columns;
    int itme_height = (texture.height + spacing) / rows;

    SpriteInfo info;

    info.TextureId = texture_id;
    info.SourceRect.width = float(item_width - spacing);
    info.SourceRect.height = float(itme_height - spacing);

    for (int y = 0; y < rows; y++)
    {
        info.SourceRect.x = 0;
        for (int x = 0; x < columns; x++)
        {
            _sprites_info.push_back(info);

            info.SourceRect.x += item_width;
        }

        info.SourceRect.y += itme_height;
    }
}

void SetSpriteOrigin(int sprite_id, int x, int y)
{
    if (sprite_id < 0 || sprite_id >= int(_sprites_info.size()))
        return;

    SpriteInfo& sprite = _sprites_info[sprite_id];
    sprite.Origin.x = float(x);
    sprite.Origin.y = float(y);
}

void SetSpriteBorders(int sprite_id, int left, int top, int right, int bottom)
{
    if (sprite_id < 0 || sprite_id >= int(_sprites_info.size()))
        return;

    SpriteInfo& sprite = _sprites_info[sprite_id];
    sprite.Borders.x = float(left);
    sprite.Borders.y = float(top);

    sprite.Borders.width = float(right);
    sprite.Borders.height = float(bottom);
}

void SetSpriteBorders(int sprite_id, int inset)
{
    if (sprite_id < 0 || sprite_id >= int(_sprites_info.size()))
        return;
    
    SpriteInfo& sprite = _sprites_info[sprite_id];
    sprite.Borders.x = float(inset);
    sprite.Borders.y = float(inset);

    sprite.Borders.width = float(sprite.SourceRect.width - inset);
    sprite.Borders.height = float(sprite.SourceRect.height - inset);

}

void CenterSprite(int sprite_id)
{
    if (sprite_id < 0 || sprite_id >= int(_sprites_info.size()))
        return;

    SpriteInfo& sprite = _sprites_info[sprite_id];
    sprite.Origin.x = sprite.SourceRect.width/2;
    sprite.Origin.y = sprite.SourceRect.height/2;
}

// TODO: implement
void FillRectWithSprite(int sprite_id, const Rectangle& rect, Color tint, uint8_t flip)
{

}

void SetupWindow()
{
    int monitor = GetCurrentMonitor();

    int max_height = GetMonitorHeight(monitor) - 40;
    if (GetScreenHeight() > max_height)
        SetWindowSize(GetScreenWidth(), max_height);

    SetExitKey(0);
    SetTargetFPS(60);

    // Image icon = LoadImage("icons/Sword.png");

    // ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    // ImageColorReplace(&icon, BLACK, BLANK);
    // ImageColorReplace(&icon, Color{ 136,136,136,255 }, BLANK);

    // SetWindowIcon(icon);

    // UnloadImage(icon);
}
