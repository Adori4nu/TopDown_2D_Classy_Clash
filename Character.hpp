#pragma once
#include <raylib.h>

#include "BaseCharacter.hpp"

class Character : public BaseCharacter
{
public:
    Character(int window_width, int window_height, Texture2D idle_texture, Texture2D run_texture, Vector2 position, float scale);

    virtual void tick(float delta_time) override;
    virtual Vector2 GetScreenPosition() const override;

    ~Character() 
    {
        UnloadTexture(_texture); 
        UnloadTexture(_idle_texture);
        UnloadTexture(_runing_texture);    
    };
private:
    int _window_width{};
    int _window_height{};
};