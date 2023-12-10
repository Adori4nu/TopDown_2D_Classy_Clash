#include "GraphicsEngine.hpp"

#include <algorithm>

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
    BeginDrawing();
    BeginMode2D(player_camera);

    player_camera.target = {_player_character->GetWorldPosition()};

    RenderWorld(_world);
    
    for (auto prop : environmentProps)
    {
        if(!prop)
            continue;
        Render(prop);
    }
    
    for (auto gameObject : gameObjects) {
        if (!gameObject)
            continue;
        switch (gameObject->GetObjectType())
        {
            case ObjectType::Base_Enemy:
                Render(static_cast<BaseEnemy*>(gameObject));
                break;
            case ObjectType::Pawn:
                Render(static_cast<Pawn*>(gameObject));
                break;
            case ObjectType::Actor:
                Render(static_cast<Actor*>(gameObject));
                break;
            default:
                break;
        }
    }
    
    Render(_player_character);

    Render(_particle_system);

    EndMode2D();

    if (!_player_character->IsAlive())
    {
        DrawText("Game Over!", _window_width / 2 - MeasureText("Game Over!", 40) / 2, _window_height / 2 - 40, 40, RED);
    }
    else
    {
        std::string player_health{"Health: "};
        player_health.append(std::to_string(_player_character->GetHealth()), 0, 3);
        DrawText(player_health.c_str(), 55, 45, 40, RED);

        std::string player_resolve{"Resolve: "};
        player_resolve.append(std::to_string(_player_character->resolve), 0, 3);
        DrawText(player_resolve.c_str(), 360, 45, 40, BLUE);

        std::string player_kills{"Kill count: "};
        player_kills.append(std::to_string(_player_character->GetKillCount()), 0, 5);
        DrawText(player_kills.c_str(), 55, 100, 30, BLACK);
        
        std::string keys{"Press: WSAD - to move, LMB - to attack, ESC - to exit."};
        DrawText(keys.c_str(), 55, 680, 20, BLACK);
    }
    // if (std::all_of(woon.cbegin(), woon.cend(), [](bool KO_val) { return KO_val; }))
    // {
    //     DrawText("You Win!", window_width / 2 - MeasureText("You Win!", 40) / 2, window_height / 2 - 40, 40, YELLOW);
    //     EndDrawing();
    //     std::ofstream file("character_data.txt");
    //     if (file.is_open()) {
    //         file << player;
    //         file.close();
    //     } else {
    //         std::cerr << "Unable to open file for writing." << std::endl;
    //     }
    //     continue;
    // }
    DrawFPS(_window_width - 60, 10);

    EndDrawing();

}

void GraphicsEngine::RenderWorld(World *world)
{
    ClearBackground(Color{99, 155, 255, 255});
    // world->SetMapPos(Vector2Scale(player_position, -1.f));
    
    std::for_each(world->tile_map.begin(), world->tile_map.end(), [world, i = 0](const auto& tile) mutable
    {
        if (tile != 0)
        {
            world->tile_destination.x = world->tile_destination.width * (float)(i % world->map_width);
            world->tile_destination.y = world->tile_destination.height * (float)(i / world->map_width);
            i++;
            world->tile_source.x = world->tile_source.width * (float)((tile-1)
             % (int)(world->GetWorldTexture().width / (int)(world->tile_source.width)));
            world->tile_source.y = world->tile_source.height * (float)((tile-1)
             / (int)(world->GetWorldTexture().width / (int)(world->tile_source.width)));
            DrawTexturePro(world->GetWorldTexture(), world->tile_source, world->tile_destination
            , Vector2{world->tile_destination.width, world->tile_destination.height}, 0, WHITE);
        }
    });
    
    // DrawTextureEx(world->GetWorldTexture(), world->GetMapPosition(), 0, 4.f, WHITE);
    // DrawTextureEx(map_texture, map_pos, 0, ASSET_SCALE, WHITE);

    // Draw the map
}

void GraphicsEngine::Render(Prop *prop)
{
    Vector2 wrld_pos = prop->GetWorldPosition();
    DrawTextureEx(prop->GetTexture(), wrld_pos, 0.f, prop->GetSpriteScale(), WHITE);
    DrawRectangleLines(wrld_pos.x
    , wrld_pos.y
    , static_cast<float>(prop->GetTexture().width) * prop->GetSpriteScale()
    , prop->GetTexture().height * prop->GetSpriteScale()
    , BLUE
    );
}

void GraphicsEngine::Render(Actor *actor)
{
    Vector2 wrld_pos = actor->GetWorldPosition();
    Rectangle source{actor->GetFrame() * actor->GetWidth(), 0.f, actor->GetRightLeftDirection() * actor->GetWidth(), actor->GetHeight()};
    Rectangle dest{wrld_pos.x, wrld_pos.y, actor->GetSpriteScale() * actor->GetWidth(), actor->GetSpriteScale() * actor->GetHeight()};
    DrawTexturePro(actor->GetTexture(), source, dest, Vector2{}, 0.f, WHITE);
    DrawRectangleLines(wrld_pos.x
    , wrld_pos.y
    , static_cast<float>(actor->GetTexture().width) / actor->GetMaxFrame() * actor->GetSpriteScale()
    , actor->GetTexture().height * actor->GetSpriteScale()
    , RED)
    ;
}

void GraphicsEngine::Render(Pawn *pawn)
{
    if (!pawn->IsAlive())
    {
        return;
    }
    auto actor = dynamic_cast<Actor*>(pawn);
    GraphicsEngine::Render(actor);
}

void GraphicsEngine::Render(BaseEnemy *enemy)
{
    if (enemy->IsAlive())
    {
        Vector2 enemy_position_center = enemy->GetEnemyCenter();
        DrawCircleLines(enemy_position_center.x
                , enemy_position_center.y
                , enemy->GetSightRadius()
                , YELLOW
                );
    }
    auto pawn = dynamic_cast<Pawn*>(enemy);
    GraphicsEngine::Render(pawn);
}

void GraphicsEngine::Render(BasePlayerCharacter *player)
{
    Vector2 player_world_pos = player->GetWorldPosition();
    Rectangle source{player->GetFrame() * player->GetWidth(), 0.f, player->GetRightLeftDirection() * player->GetWidth(), player->GetHeight()};
    Rectangle dest{player_world_pos.x, player_world_pos.y, player->GetSpriteScale() * player->GetWidth(), player->GetSpriteScale() * player->GetHeight()};
    DrawTexturePro(player->GetTexture(), source, dest, Vector2{}, 0.f, WHITE);
    
    source = {0.0f, 0.0f, static_cast<float>(player->GetWeaponTexture().width) * player->GetRightLeftDirection(), static_cast<float>(player->GetWeaponTexture().height)};
    dest = {player_world_pos.x + player->GetWeaponOriginOffset().x, player_world_pos.y + player->GetWeaponOriginOffset().y, static_cast<float>(player->GetWeaponTexture().width) * player->GetWeaponScale(), static_cast<float>(player->GetWeaponTexture().height) * player->GetWeaponScale()};
    DrawTexturePro(player->GetWeaponTexture(), source, dest, player->GetWeaponOrigin(), player->GetWeaponRotation(), WHITE);
    DrawRectangleLines(player->GetCollisionRectangle().x
    , player->GetCollisionRectangle().y
    , player->GetCollisionRectangle().width
    , player->GetCollisionRectangle().height
    , GREEN
    );
}

void GraphicsEngine::Render(ParticleSystem *particle_system)
{
    for (auto& particle : particle_system->GetParticles())
    {
        if (!particle.Active)
            continue;
        
        float life = particle.LifeRamaining / particle.LifeTime;
        Vector3 rgb = Vector3Lerp(particle.ColorBegin, particle.ColorEnd, life);
        Color color {(unsigned char)rgb.x, (unsigned char)rgb.y, (unsigned char)rgb.z, 255};
        color.a = color.a * life;

        float size = Lerp(particle.SizeEnd, particle.SizeBegin, life);

        switch (particle.type)
        {
        case PLAYER_HIT:
        case PLAYER_CRITICAL_HIT:
        case ENEMY_HIT:
        case ENEMY_CRITITCAL_HIT:
            DrawTextPro(
                GetFontDefault()
                , std::to_string(particle.Damage).c_str()
                , particle.Position
                , particle.CharacterOrigin
                , 0.f, (int)size * 12, 0, color
            );
            break;
        case HEAL:
            DrawTextPro(
                GetFontDefault()
                , std::to_string(particle.Damage).c_str()
                , particle.Position
                , particle.CharacterOrigin
                , 0.f, (int)size * 6, 4, color
            );
            break;
        case MISS:
            DrawTextPro(
                GetFontDefault()
                , particle.Miss
                , particle.Position
                , particle.CharacterOrigin
                , particle.Rotation * 15.f, (int)size * 6, 4, color
            );
            break;
        case DODGE:
            DrawTextPro(
                GetFontDefault()
                , particle.Dodge
                , particle.Position
                , particle.CharacterOrigin
                , particle.Rotation * 15.f, (int)size * 6, 4, color
            );
            break;
        }
    }
    
}
