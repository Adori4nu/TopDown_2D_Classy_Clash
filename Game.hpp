#pragma once

// class Actor;
// class BaseEnemy;
// class BasePlayerCharacter;
// class GameObject;
// class Pawn;
// class Prop;
// class World;

// class makes no sense right now
// class Game
// {
// public:
// int width, int height, int target_framerate, std::string game_title
    // Game();
    // Game(const Game& other) = delete;
    // Game& operator=(const Game& other) = delete;

    // ~Game() noexcept;

    // bool GameShouldClose() const;
    // void Tick();
    void InitGame();
    void ActivateGame();
// private:
    void UpdateGame(bool& should_stop_playing);
    void QuitGame();
    // void Draw();

    // World _world{GetTexture(TextureIDs::TileSetTexture)};
    // ParticleSystem damage_number_popups;
    // std::vector<Prop> environmentProps;
    // std::vector<GameObject> gameObjects;
    // BasePlayerCharacter _player_character{ObjectType::Base_Player, window_width, window_height, GetTexture(TextureIDs::Actors::player_idle_texture), GetTexture(TextureIDs::Actors::player_runing_texture), ASSET_SCALE, damage_number_popups};
// };

