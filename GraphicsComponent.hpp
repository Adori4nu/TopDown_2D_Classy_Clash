#pragma once
#include "include/raylib.h"

struct GraphicsComponent
{
    int idle_texture_id_{-1};
    int runing_texture_id_{-1};
    int frame{};
    int max_frame{6};
    Rectangle source_{};
    Rectangle destination_{};
    Color tint_{WHITE};
    bool shadow_{false};
};
