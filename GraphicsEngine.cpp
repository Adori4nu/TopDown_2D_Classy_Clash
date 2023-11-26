#include "GraphicsEngine.hpp"

#include "Actor.hpp"
#include "BaseEnemy.hpp"
#include "BasePlayerCharacter.hpp"
#include "Pawn.hpp"
#include "Prop.hpp"
#include "World.hpp"

#include "include/raylib.h"
#include "GraphicsEngine.hpp"

// std::unique_ptr<GraphicsEngine> instance = nullptr;

void GraphicsEngine::RenderAll()
{
    Vector2 player_position = _player_character->GetWorldPosition();
    
    RenderWorld(_world, player_position);
    
    for (auto prop : environmentProps)
    {
        if(!prop)
            continue;
        Render(prop, player_position);
    }
    
    for (auto gameObject : gameObjects) {
        if (!gameObject)
            continue;
        switch (gameObject->GetObjectType())
        {
            case ObjectType::Base_Enemy:
                Render(static_cast<BaseEnemy*>(gameObject), player_position);
                break;
            case ObjectType::Pawn:
                Render(static_cast<Pawn*>(gameObject), player_position);
                break;
            case ObjectType::Actor:
                Render(static_cast<Actor*>(gameObject), player_position);
                break;
            default:
                break;
        }
    }

    Render(_player_character);
    
}

void GraphicsEngine::RenderWorld(World *world, Vector2 player_position)
{
    ClearBackground(Color{99, 155, 255, 255});
    world->SetMapPos(Vector2Scale(player_position, -1.f));
    // map_pos = Vector2Scale(player.GetWorldPosition(), -1.f);
    DrawTextureEx(world->GetWorldTexture(), world->GetMapPosition(), 0, 4.f, WHITE);
    // DrawTextureEx(map_texture, map_pos, 0, ASSET_SCALE, WHITE);

    // Draw the map
}

void GraphicsEngine::Render(Prop *prop, Vector2 player_position)
{
    Vector2 screen_position {Vector2Subtract(prop->GetWorldPosition(), player_position)};
    DrawTextureEx(prop->GetTexture(), screen_position, 0.f, prop->GetSpriteScale(), WHITE);
    DrawRectangleLines(screen_position.x
    , screen_position.y
    , static_cast<float>(prop->GetTexture().width) * prop->GetSpriteScale()
    , prop->GetTexture().height * prop->GetSpriteScale()
    , BLUE
    );
}

void GraphicsEngine::Render(Actor *actor, Vector2 player_position)
{
    Vector2 screen_pos = actor->GetScreenPosition(player_position);
    // DrawTextureEx(_texture, screen_pos, 0.f, sprite_scale, WHITE);
    Rectangle source{actor->GetFrame() * actor->GetWidth(), 0.f, actor->GetRightLeftDirection() * actor->GetWidth(), actor->GetHeight()};
    Rectangle dest{screen_pos.x, screen_pos.y, actor->GetSpriteScale() * actor->GetWidth(), actor->GetSpriteScale() * actor->GetHeight()};
    DrawTexturePro(actor->GetTexture(), source, dest, Vector2{}, 0.f, WHITE);
    DrawRectangleLines(screen_pos.x
    , screen_pos.y
    , static_cast<float>(actor->GetTexture().width) / actor->GetMaxFrame() * actor->GetSpriteScale()
    , actor->GetTexture().height * actor->GetSpriteScale()
    , RED)
    ;
}

void GraphicsEngine::Render(Pawn *pawn, Vector2 player_position)
{
    if (!pawn->IsAlive())
    {
        return;
    }
    auto actor = dynamic_cast<Actor*>(pawn);
    GraphicsEngine::Render(actor, player_position);
}

void GraphicsEngine::Render(BaseEnemy *enemy, Vector2 player_position)
{
    auto pawn = dynamic_cast<Pawn*>(enemy);
    GraphicsEngine::Render(pawn, player_position);
}

void GraphicsEngine::Render(BasePlayerCharacter *player)
{
    Rectangle source{player->GetFrame() * player->GetWidth(), 0.f, player->GetRightLeftDirection() * player->GetWidth(), player->GetHeight()};
    Rectangle dest{player->GetScreenPosition().x, player->GetScreenPosition().y, player->GetSpriteScale() * player->GetWidth(), player->GetSpriteScale() * player->GetHeight()};
    DrawTexturePro(player->GetTexture(), source, dest, Vector2{}, 0.f, WHITE);
    
    source = {0.0f, 0.0f, static_cast<float>(player->GetWeaponTexture().width) * player->GetRightLeftDirection(), static_cast<float>(player->GetWeaponTexture().height)};
    dest = {player->GetScreenPosition().x + player->GetWeaponOriginOffset().x, player->GetScreenPosition().y + player->GetWeaponOriginOffset().y, static_cast<float>(player->GetWeaponTexture().width) * player->GetWeaponScale(), static_cast<float>(player->GetWeaponTexture().height) * player->GetWeaponScale()};
    DrawTexturePro(player->GetWeaponTexture(), source, dest, player->GetWeaponOrigin(), player->GetWeaponRotation(), WHITE);
    DrawRectangleLines(player->GetCollisionRectangle().x
    , player->GetCollisionRectangle().y
    , player->GetCollisionRectangle().width
    , player->GetCollisionRectangle().height
    , GREEN
    );
}
