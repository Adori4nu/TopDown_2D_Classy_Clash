#include "Screen.hpp"
#include "BasePlayerCharacter.hpp"
#include "helperFunctions.hpp"
#include "GraphicsEngine.hpp"
#include "gameConstants.hpp"
#include "Item.hpp"
#include "Main.hpp"

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
    // float rect_height = float(_button_font_size) + (_button_border * 2.0f);
    float text_width = (float)(MeasureText(text, _button_font_size));

    float text_X_origin = GetScreenWidth() / 4.0f - text_width / 2.0f;
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
    // float rect_height = _button_font_size + (_button_border * 2.0f);
    float text_width = (float)(MeasureText(text, _button_font_size));

    float text_X_origin = GetScreenWidth() / 2.0f - text_width / 2.0f;
    float text_Y_origin = y - _button_font_size / 2.0f;

    Rectangle button_rect{ text_X_origin - _button_border
                        , text_Y_origin - _button_border
                        , text_width + (_button_border * 2.0f)
                        , _button_font_size + (_button_border * 2.0f)
                        };

    bool hovered = RectIsHover(button_rect);
    // if (hovered && !mouse_on_button)
    // {
    //     PlaySound(SoundIds::sfx::HoveredSound);
    //     mouse_on_button = true;
    // }
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
    float barHeight{ GetScreenHeight() - 80.f };

    DrawRectangleRec(Rectangle{ GetScreenWidth() / 16.f * 5.f , barHeight, float(GetScreenWidth() / 8.f * 3), 80.f }, WHITE);

    float buttonX{ window_width * 0.75f + 64.f };
    float buttonY{ window_height - 80.f };
    if ((DrawButton(buttonX, buttonY, TextureIDs::SpriteIDs::UI::equipment_sprite, 0, PURPLE, WHITE, 2.f, 0.f, 0.f) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))  || IsKeyPressed(KEY_I))
        InventoryOpen = !InventoryOpen;

    DrawText("Inventory - I", buttonX, buttonY + ButtonSize + 4, 8, BLACK);

    buttonX += 72.f;
    if ((DrawButton(buttonX, buttonY, TextureIDs::SpriteIDs::UI::equipment_sprite, 0, PURPLE, WHITE, 2.f, 0.f, 0.f) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))  || IsKeyPressed(KEY_B))
        EquipmentOpen = !EquipmentOpen;
    
    DrawText("Character - B", buttonX, buttonY + ButtonSize + 4, 8, BLACK);

    if (InventoryOpen || EquipmentOpen)
    {
        GameHUDOpen();

        if (InventoryOpen)
        DrawInventory();

        if (EquipmentOpen)
        DrawEquipment();
    }

    if (!InventoryOpen && !EquipmentOpen)
    {
        GameHUDClosed();
    }
}

bool GameHudScreen::IsUiClick(const Vector2& pos)
{
    if (pos.y > GetScreenHeight() - 80.f)
        return true;

    Rectangle InventoryWindowRect{ window_width - 1000.f, window_height - 640.f, 354.f , 400.f };
    Rectangle EquipmentWindowRect{ window_height - 120.f, window_height - 640.f, 354.f , 400.f };
    // DrawRectangleLines( window_height - 120.f, window_height - 640.f, 354.f , 400.f RED);
    if (InventoryOpen && CheckCollisionPointRec(pos, InventoryWindowRect))
        return true;
    
    if (EquipmentOpen && CheckCollisionPointRec(pos, EquipmentWindowRect))
        return true;

    return false;
}

bool GameHudScreen::DrawButton(float x, float y, int itemId, int quantity, Color border, Color inside, float scale, float inside_alpha, float borde_alpha)
{
    Rectangle buttonRectangle{ x, y, ButtonSize, ButtonSize };
    DrawRectangleRec(buttonRectangle, ColorAlpha(border, borde_alpha));
    DrawRectangleRec(Rectangle{ x + ButtonInset, y + ButtonInset, ButtonSize - ButtonInset * 2, ButtonSize - ButtonInset * 2 }, ColorAlpha(inside, inside_alpha));

    if (itemId != -1)
    {
        Texture& texture{GetTexture(itemId)};
        Rectangle source{ 0, 0, float(texture.width), float(texture.height) };
        Rectangle dest{ x, y, texture.width * scale, texture.height * scale };
        // Vector2 center{ x + ButtonSize / 2, y + ButtonSize / 2 };
        DrawTexturePro( texture, source, Rectangle{ x + 2, y + 2, (source.width + 2) * scale, (source.height + 2) * scale }
        , Vector2{ 0,0 }, 0.f, BLACK);
        DrawTexturePro( texture, source, dest
        , Vector2{ 0,0 }, 0.f, WHITE);
    }

    if (quantity > 1)
	{
		DrawText(TextFormat("X%d", quantity), int(x + ButtonSize/2), int(y + ButtonSize - 22), 20, WHITE);
	}

    return CheckCollisionPointRec(GetMousePosition(), buttonRectangle);
}

void GameHudScreen::DrawInventory()
{
    Rectangle inventoryWindowRect{ window_width - 420.f, window_height - 640.f, 354.f , 520.f };
    Rectangle inventoryShadow{ inventoryWindowRect };
    inventoryShadow.x += 10;
    inventoryShadow.y += 10;

    DrawRectangleRec(inventoryShadow, ColorAlpha(BLACK, 0.5f));
    NPatchInfo info;
    Texture2D& texture{GetTexture(TextureIDs::SpriteIDs::UI::inventory_sprite)};
    info.source = Rectangle{ 0, 0, float(texture.width), float(texture.height) };
    info.left = 4;
    info.top = 4;
    info.right = 4;
    info.bottom = 4;
    info.layout = NPATCH_NINE_PATCH;
    DrawTextureNPatch(texture, info, inventoryWindowRect, Vector2{ 0,0 }, 0.f, WHITE);

    constexpr int inventory_item_size{ 64 };
    constexpr int inventory_item_padding{ 4 };

    int itemIndex{ 0 };
    for (int y{ 0 }; y < 7; y++)
    {
        for (int x{ 0 }; x < 5; x++)
        {
            float itemY = inventoryWindowRect.y + (inventoryWindowRect.height - inventory_item_padding) - ((inventory_item_padding + inventory_item_size) * (7 - y));
            float itemX = inventoryWindowRect.x + (inventory_item_padding * 2) + ((inventory_item_size + inventory_item_padding) * x);

            Rectangle itemRect = { itemX, itemY, inventory_item_size, inventory_item_size };
            Rectangle shadowRect = itemRect;
            shadowRect.x += 2;
            shadowRect.y += 2;

            DrawRectangleRec(shadowRect, ColorAlpha(BLACK, 0.5f));
            FillRectWithSprite(TextureIDs::SpriteIDs::UI::inventory_sprite, itemRect);

            if (itemIndex < player_character.BackpackContent.size())
            {
                Item* item = GetItem(player_character.BackpackContent[itemIndex].ItemId);
                if (item != nullptr)
                {
                    Texture& texture{GetTexture(item->_texture_id)};
                    Rectangle source{ 0, 0, float(texture.width), float(texture.height) };
                    Rectangle dest{ itemRect.x, itemRect.y, texture.width * 2.f , texture.height * 2.f };
                    DrawTexturePro( texture, source, Rectangle{ itemRect.x + 2, itemRect.y + 2, (source.width + 2) * 2.f, (source.height + 2) * 2.f }
                    , Vector2{ 0,0 }, 0.f, BLACK);
                    DrawTexturePro( texture, source, dest
                    , Vector2{ 0,0 }, 0.f, WHITE);

                    if (player_character.BackpackContent[itemIndex].Quantity > 1)
                        DrawText(TextFormat("%d", player_character.BackpackContent[itemIndex].Quantity), int(itemRect.x) + 2, int(itemRect.y + itemRect.height - 10), 10, WHITE);

                    bool hovered = CheckCollisionPointRec(GetMousePosition(), itemRect);

                    if (hovered)
                    {
                        HoveredItem = item;
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        {
                            if (item->IsActivatable() && player_character.ActivateItemCallback != nullptr)
                                player_character.ActivateItemCallback(itemIndex);
                            else if (item->IsWeapon() && player_character.EquipWeaponCallback != nullptr)
                                player_character.EquipWeaponCallback(itemIndex);
                            else if (item->IsArmor() && player_character.EquipArmorCallback != nullptr)
                                player_character.EquipArmorCallback(itemIndex);
                        }
                        else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && player_character.DropItemCallback != nullptr)
                        {
                            player_character.DropItemCallback(itemIndex);
                        }
                    }
                }
            }
            itemIndex++;
        }
    }
}

void GameHudScreen::DrawEquipment()
{
    Rectangle equipmentWindowRect{ window_width - 1180.f, window_height - 640.f, 354.f , 520.f };
    Rectangle equipmentShadow{ equipmentWindowRect };
    equipmentShadow.x += 10;
    equipmentShadow.y += 10;

    DrawRectangleRec(equipmentShadow, ColorAlpha(BLACK, 0.5f));
    NPatchInfo info;
    Texture2D& texture{GetTexture(TextureIDs::SpriteIDs::UI::inventory_sprite)};
    info.source = Rectangle{ 0, 0, float(texture.width), float(texture.height) };
    info.left = 4;
    info.top = 4;
    info.right = 4;
    info.bottom = 4;
    info.layout = NPATCH_NINE_PATCH;
    DrawTextureNPatch(texture, info, equipmentWindowRect, Vector2{ 0,0 }, 0.f, WHITE);
}