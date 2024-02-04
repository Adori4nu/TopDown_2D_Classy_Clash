#pragma once

enum class AppState
{
    Startup,
    Loading,
    Menu,
    Running,
    InPlayerUI,
    Paused,
    GameOver,
    Quitting
};