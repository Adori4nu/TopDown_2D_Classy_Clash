#pragma once
#include "include/raylib.h"

#include "Main.hpp"

#include <string>

class BasePlayerCharacter;

// implement Draw Functions for Screens
class Screen
{
public:
    virtual void Draw() = 0;

protected:
    bool RectIsHover(Rectangle& rect);
    void DrawCenteredText(int y, const char* text, int font_size, Color color);
    bool ToLeftButton(int y, const char* text);
    bool CenteredButton(int y, const char* text);
    void DimSceen(float alpha = 0.75f);

    Color ButtonColor{ WHITE };
    Color ButtonHilight{ PINK };
    Color ButtonPressColor{ DARKPURPLE };

    int _button_font_size = 60;
    int _button_border = 10;
};

void SetActiveScreen(Screen* screen);

class LoadingScreen : public Screen
{
public:
    std::string LoadingText{ "Loading..." };

    LoadingScreen()
    {
        int size = MeasureText(LoadingText.c_str(), 20);
        origin.x = GetScreenWidth() * 0.5f - size * 0.5f;
        origin.y = GetScreenHeight() * 0.5f - 10;

        left_spinner.x = origin.x - 25.f;
        right_spinner.x = origin.x + size + 25.0f;
        left_spinner.y = right_spinner.y = GetScreenHeight() * 0.5f;

        left_spinner.width = right_spinner.width = 20;
        left_spinner.height = right_spinner.height = 20;
    }

    
    void Draw() override
    {
        // tell them we are loading
        DrawText(LoadingText.c_str(), int(origin.x), int(origin.y), 20, WHITE);

        // some spinny things to know that the app hasn't locked up
        DrawRectanglePro(left_spinner, Vector2{ 10, 10 }, float(GetTime()) * 180.0f, BLUE);
        DrawRectanglePro(right_spinner, Vector2{ 10, 10 }, float(GetTime()) * -180.0f, BLUE);

        // progress bar.
        float progressWidth = right_spinner.x - left_spinner.x;
        DrawRectangle(int(left_spinner.x), int(left_spinner.y + 20), (int)(progressWidth * load_proggres), 5, RAYWHITE);
    }


    Vector2 origin{ 0,0 };

    Rectangle left_spinner{ 0,0 };
    Rectangle right_spinner{ 0,0 };

    float load_proggres{ 0.f };
};

class MainMenuScreen : public Screen
{
public:
    void Draw() override
    {
        // dim the background
        DimSceen();

        // title
        DrawCenteredText(40, "My Rougelite", 40, BLUE);

        // version and copyright
        DrawText(VersionStr, 2, GetScreenHeight() - 10, 10, GRAY);
        DrawText(CopyrightString, GetScreenWidth() - 2 - MeasureText(CopyrightString, 10), GetScreenHeight() - 10, 10, GRAY);

        // play button
        if (CenteredButton(GetScreenHeight() / 4, "Play"))
            StartGame();
        
        // options button
        CenteredButton(GetScreenHeight()/2, "Options");

        // quit button
        if (CenteredButton(GetScreenHeight() - (GetScreenHeight() / 4), "Quit"))
            QuitApplication();
    }
};

class GameOverScreen : public Screen
{
public:
    void Draw() override
    {
        // dim the background
        DimSceen();

        // title
        DrawCenteredText(40, "", 40, BLUE);


        // win state
        if (_player_won)
            DrawCenteredText(120, "Congratulations You WON!", 60, WHITE);
        else
            DrawCenteredText(120, "You died, better luck next time.", 60, RED);

        // score
        DrawCenteredText(200, TextFormat("Score = %d", _player_gold), 60, YELLOW);

        // version and copyright
        DrawText(VersionStr, 2, GetScreenHeight() - 10, 10, GRAY);
        DrawText(CopyrightString, GetScreenWidth() - 2 - MeasureText(CopyrightString, 10), GetScreenHeight() - 10, 10, GRAY);

        // main menu button
        if (CenteredButton(GetScreenHeight() / 2, "Main Menu"))
            GoToMainMenu();

        // quit button
        if (CenteredButton(GetScreenHeight() - (GetScreenHeight() / 4), "Quit"))
            QuitApplication();
    }
    bool _player_won{false};
    int _kills{};
    int _player_gold{};
};

class PauseMenuScreen : public Screen
{
public:
    void Draw() override
    {
        DimSceen();

        // DrawCenteredText(40, "", 40, BLUE);
        DrawCenteredText(105, "Paused", 60, RED);

        DrawText(VersionStr, 2, GetScreenHeight() - 10, 10, GRAY);
        DrawText(CopyrightString, GetScreenWidth() - 2 - MeasureText(CopyrightString, 10), GetScreenHeight() - 10, 10, GRAY);

        if (CenteredButton(GetScreenHeight() / 4, "Resume"))
            ResumeGame();

        if (CenteredButton(GetScreenHeight() / 2, "Quit to Menu"))
            GoToMainMenu();

        if (CenteredButton(GetScreenHeight() - (GetScreenHeight() / 4), "Quit to Desktop"))
            QuitApplication();
    }
};

class GameHudScreen : public Screen
{
public:
    GameHudScreen(BasePlayerCharacter& player) : player_character(player){};

    // TODO: implement all the functions
    void Draw() override;

    BasePlayerCharacter& player_character;
    bool IsUiClick(const Vector2& pos);
    bool InventoryOpen = false;
    
private:
	bool DrawButton(float x, float y, int itemId = -1, int quantity = 1, Color border = BROWN, Color center = BEIGE);
	void DrawInventory();	
	// void ShowItemToolTip(const Item* item, const Rectangle& rect);

private:
	float ButtonSize = 70;
	float ButtonInset = 6;

	// const Item* HoveredItem = nullptr;
};