#pragma once
#include "appState.hpp"

constexpr char VersionStr[] = "v 0.1.03012024";
constexpr char CopyrightString[] = "Copyright 2024 Adrian Kowarik";

void LoadComplete();

void GoToMainMenu();
void UpdateMainMenu();
// void UpdateInventory();
// void UpdateEquipment();
// void UpdateOptions();
void GameHUDOpen();
void GameHUDClosed();
bool UpdateGameHUD(AppState& game_state);
void StartGame();
void PauseGame();
void ResumeGame();
void EndGame(bool win, int kill_count, int gold);
void QuitApplication();

bool SearchAndSetResourceDir(const char* folderName);
