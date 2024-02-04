#pragma once
#include <vector>

#include "appState.hpp"
#include "SceneType.hpp"

// class Actor;
class BaseEnemy;
class BasePlayerCharacter;
// class GameObject;
// class Pawn;
// class Prop;
class ParticleSystem;
class World;

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
// private:
    // void Draw();

    // World _world{GetTexture(TextureIDs::TileSetTexture)};
    // ParticleSystem damage_number_popups;
    // std::vector<Prop> environmentProps;
    // std::vector<GameObject> gameObjects;
    // BasePlayerCharacter _player_character{ObjectType::Base_Player, window_width, window_height, GetTexture(TextureIDs::Actors::player_idle_texture), GetTexture(TextureIDs::Actors::player_runing_texture), ASSET_SCALE, damage_number_popups};
// };

void InitGame();
void ActivateGame();
void UpdateGame(AppState& game_state);
void QuitGame();
float GetGameClock();
std::vector<BaseEnemy>& GetEnemyPool();
BasePlayerCharacter& GetPlayerCharacter();
World& GetWorld();
ParticleSystem& GetParticleSystem();
SceneType GetSceneType();