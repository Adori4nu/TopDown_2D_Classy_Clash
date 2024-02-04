#include "include/raylib.h"
#include "include/raymath.h"
#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "Main.hpp"
#include "appState.hpp"
#include "BasePlayerCharacter.hpp"
#include "BaseEnemy.hpp"
#include "Game.hpp"
#include "gameConstants.hpp"
#include "GameObject.hpp"
#include "GraphicsEngine.hpp"
#include "helperFunctions.hpp"
#include "Prop.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Screen.hpp"
#include "World.hpp"

AppState applicationState = AppState::Startup;

MainMenuScreen MainMenu;
GameOverScreen GameOver;
PauseMenuScreen PauseMenu;

void LoadComplete()
{
    applicationState = AppState::Menu;
    SetActiveScreen(&MainMenu);

    // _world.LoadMap();
}

void GoToMainMenu()
{
    if (applicationState == AppState::Running || applicationState == AppState::Paused)
        QuitGame();

    StartBGM("sounds/marvin03 brigth.ogg");

    LoadComplete();
}

void UpdateMainMenu()
{
    if (IsKeyPressed(KEY_ESCAPE))
        QuitApplication();
}

// void UpdateInventory()
// {
// }

// void UpdateEquipment()
// {
// }

// void UpdateOptions()
// {
// }

void GameHUDOpen()
{
    applicationState = AppState::InPlayerUI;
}

void GameHUDClosed()
{
    applicationState = AppState::Running;
}

bool UpdateGameHUD(AppState& game_state)
{

    return false;
}

void StartGame()
{
    applicationState = AppState::Running;
    SetActiveScreen(nullptr);
    StopBGM();
    InitGame();
}

void PauseGame()
{
    applicationState = AppState::Paused;
}

void ResumeGame()
{
    applicationState = AppState::Running;
    SetActiveScreen(nullptr);
    ActivateGame();
}

void EndGame(bool win, int kill_count, int gold)
{
    applicationState = AppState::GameOver;
    SetActiveScreen(&GameOver);
    GameOver._player_won = win;
    GameOver._kills = kill_count;
    GameOver._player_gold = gold;
}

void QuitApplication()
{
    applicationState = AppState::Quitting;
}

void UpdatePaused()
{
	SetActiveScreen(&PauseMenu);

	if (IsKeyPressed(KEY_ESCAPE))
		ResumeGame();
}

bool SearchAndSetResourceDir(const char *folder_name)
{
    if (DirectoryExists(folder_name))
    {
        ChangeDirectory(TextFormat("%s/%s", GetWorkingDirectory(), folder_name));
        return true;
    }

    const char* app_dir{GetApplicationDirectory()};

    const char* dir{TextFormat("%s%s", app_dir, folder_name)};
    if (DirectoryExists(dir))
    {
        ChangeDirectory(dir);
        return true;
    }

    dir = TextFormat("%s../%s", app_dir, folder_name);
    if (DirectoryExists(dir))
    {
        ChangeDirectory(dir);
        return true;
    }

    dir = TextFormat("%s../../%s", app_dir, folder_name);
    if (DirectoryExists(dir))
    {
        ChangeDirectory(dir);
        return true;
    }

    dir = TextFormat("%s../../../%s", app_dir, folder_name);
    if (DirectoryExists(dir))
    {
        ChangeDirectory(dir);
        return true;
    }

    return false;
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    Random::Init();
    auto& Graphics_Engine_ = GraphicsEngine::Get();

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(window_width, window_height, "Top Down 2D Rougelite");
    SetupWindow();

    SearchAndSetResourceDir("resources");
    InitAudio();
    InitResources();

    applicationState = AppState::Loading;
    bool stop_playing{false};
    // Fix button to stop looping audio on hover
    // !stop_playing
                    // Windowshouldclose() &&
    while(!WindowShouldClose() && applicationState != AppState::Quitting)
    {
        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        switch (applicationState)
        {
            using enum AppState;
        case Loading:
            UpdateLoad();
            break;

        case Menu:
            UpdateMainMenu();
            break;

        case Running:
            UpdateGame(applicationState);
            break;

        case InPlayerUI:
            UpdateGameHUD(applicationState);
            break;
            
        case Paused:
            UpdatePaused();
            break;
        }
        Graphics_Engine_.RenderAll(applicationState);
        UpdateAudio();
    }
    
    std::ofstream file("../character_data.txt");
    if (file.is_open()) {
        file << GetPlayerCharacter();
        file.close();
        std::cout << "SAVED!!!\n";
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    ShutdownAudio();
    CleanupResources();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    std::cin.get();
    return 0;
}