#include "Screen.hpp"
#include "BasePlayerCharacter.hpp"
#include "helperFunctions.hpp"
#include "GraphicsEngine.hpp"

Screen* ActiveScreen = nullptr;

bool Screen::RectIsHover(Rectangle &rect)
{
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

void Screen::DrawCenteredText(int y, const char *text, int font_size, Color color)
{
    int textWidth = MeasureText(text, font_size);
    DrawText(text, GetScreenWidth() / 2 - textWidth / 2, y - font_size/ 2, font_size, color);
}

bool Screen::ToLeftButton(int y, const char *text)
{
    float rect_height = _button_font_size + (_button_border * 2.0f);
    float text_width = (float)(MeasureText(text, _button_font_size));

    float text_X_origin = GetScreenWidth() / 2.0f - text_width / 2.0f;
    float text_Y_origin = y - _button_font_size / 2.0f;

    Rectangle button_rect{ text_X_origin - _button_border
                        , text_Y_origin - _button_border
                        , text_width + (_button_border * 2.0f)
                        , _button_font_size + (_button_border * 2.0f)
                        };

    bool hovered = RectIsHover(button_rect);
    bool down = hovered & IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    Color color = hovered ? (down ? ButtonPressColor : ButtonHilight) : (ButtonColor);

    DrawRectangleRec(button_rect, ColorAlpha(color, 0.25f));
    DrawText(text, int(text_X_origin), int(text_Y_origin), _button_font_size, color);
    DrawRectangleLinesEx(button_rect, 2, color);

    bool clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (clicked)
	    PlaySound(SoundIds::sfx::ClickSound);

    return clicked;
}

static bool mouse_on_button = {false};

bool Screen::CenteredButton(int y, const char* text)
{
    float rect_height = _button_font_size + (_button_border * 2.0f);
    float text_width = (float)(MeasureText(text, _button_font_size));

    float text_X_origin = GetScreenWidth() / 2.0f - text_width / 2.0f;
    float text_Y_origin = y - _button_font_size / 2.0f;

    Rectangle button_rect{ text_X_origin - _button_border
                        , text_Y_origin - _button_border
                        , text_width + (_button_border * 2.0f)
                        , _button_font_size + (_button_border * 2.0f)
                        };

    bool hovered = RectIsHover(button_rect);
    if (hovered && !mouse_on_button)
    {
        PlaySound(SoundIds::sfx::HoveredSound);
        mouse_on_button = true;
    }
    mouse_on_button = hovered;

    bool down = hovered & IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    Color color = hovered ? (down ? ButtonPressColor : ButtonHilight) : (ButtonColor);

    DrawRectangleRec(button_rect, ColorAlpha(color, 0.25f));
    DrawText(text, int(text_X_origin), int(text_Y_origin), _button_font_size, color);
    DrawRectangleLinesEx(button_rect, 2, color);

    bool clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (clicked)
	    PlaySound(SoundIds::sfx::ClickSound);

    return clicked;
}

void Screen::DimSceen(float alpha)
{
    DrawRectangle(0,0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, alpha));
}

void SetActiveScreen(Screen *screen)
{
    ActiveScreen = screen;
    auto& graphic_engine = GraphicsEngine::Get();
    graphic_engine.SetScreenToRender(ActiveScreen);
}

void GameHudScreen::Draw()
{

}

bool GameHudScreen::IsUiClick(const Vector2& pos)
{
    return false;
}

bool GameHudScreen::DrawButton(float x, float y, int itemId, int quantity, Color border, Color center)
{
    return false;
}

void GameHudScreen::DrawInventory()
{

}