#include "GraphicsEngine.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "Actor.hpp"
#include "BaseEnemy.hpp"
#include "BasePlayerCharacter.hpp"
#include "Game.hpp"
#include "Pawn.hpp"
#include "Prop.hpp"
#include "Screen.hpp"
#include "World.hpp"

#include "include/raylib.h"
#include "GraphicsEngine.hpp"

GraphicsEngine GraphicsEngine::s_Instance;

bool operator!= (const Vector2& lhs,const Vector2& rhs) noexcept
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

bool operator== (const Vector2& lhs,const Vector2& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

void GraphicsEngine::RenderAll(AppState app_state)
{
    BeginDrawing();
    if (active_screen)
    {
        switch (app_state)
        {
            using enum AppState;
        case Loading:
        case Menu:
            active_screen->Draw();
            EndDrawing();
            ClearBackground(Color{0, 0, 0, 255});
            return;
        case Paused:
        case GameOver:
            active_screen->Draw();
            EndDrawing();
            break;
        default:
            break;
        }
    }

    if (!_world || !_player_camera)
    {
        EndDrawing();
        return;
    }

    BeginMode2D(*_player_camera);

    _player_camera->target = {_player_character->GetWorldPosition()};

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

    Render(_damage_number_popups);

    EndMode2D();

    if (!(_player_character->GetHealthComponent().is_alive))
    {
        DrawText("Game Over!", _window_width / 2 - MeasureText("Game Over!", 40) / 2, _window_height / 2 - 40, 40, RED);
    }
    else
    {
        std::string player_health{"Health: "};
        player_health.append(std::to_string(_player_character->GetHealthComponent().GetHealth()), 0, 3);
        DrawText(player_health.c_str(), 55, 45, 40, RED);

        std::string player_resolve{"Resolve: "};
        player_resolve.append(std::to_string(_player_character->resolve), 0, 3);
        DrawText(player_resolve.c_str(), 360, 45, 40, BLUE);

        std::string player_kills{"Kill count: "};
        player_kills.append(std::to_string(_player_character->GetKillCount()), 0, 5);
        DrawText(player_kills.c_str(), 55, 100, 30, BLACK);
        
        std::string keys{"Press: WSAD - to move, LMB - to attack, ESC - to exit."};
        DrawText(keys.c_str(), 55, 600, 20, BLACK);
    }

    if (active_screen)
    {
        switch (app_state)
        {
            using enum AppState;
        case Running:
        case InPlayerUI:
            active_screen->Draw();
            break;
        case Paused:
        case GameOver:
            active_screen->Draw();
            EndDrawing();
            return;
        default:
            break;
        }
    }

    RenderGameClock(GetGameClock());

    DrawFPS(_window_width - 60, 10);

    EndDrawing();

}

void GraphicsEngine::RenderWorld(World *world)
{
    ClearBackground(Color{99, 155, 255, 255});
    // Draw the map
    
    std::for_each(world->tile_map.begin(), world->tile_map.end(), [world, i = 0](const auto& tile) mutable
    {
        if (tile.tile_content_id != 0)
        {
            world->tile_destination.x = world->tile_destination.width * (float)(i % world->map_width);
            world->tile_destination.y = world->tile_destination.height * (float)(i / world->map_width);
            i++;
            world->tile_source.x = world->tile_source.width * (float)((tile.tile_content_id-1)
             % (int)(world->GetWorldTexture().width / (int)(world->tile_source.width)));
            world->tile_source.y = world->tile_source.height * (float)((tile.tile_content_id-1)
             / (int)(world->GetWorldTexture().width / (int)(world->tile_source.width)));
            DrawTexturePro(world->GetWorldTexture(), world->tile_source, world->tile_destination
            , Vector2{world->tile_destination.width, world->tile_destination.height}, 0, WHITE);
        }
    });
}

void GraphicsEngine::Render(Prop *prop)
{
    Vector2 wrld_pos = prop->GetWorldPosition();
    const auto& texture = GetTexture(prop->GetSpriteComponent().idle_texture_id_) ;
    DrawTextureEx(texture, wrld_pos, 0.f, prop->GetSpriteScale(), WHITE);
    DrawRectangleLines(wrld_pos.x
    , wrld_pos.y
    , static_cast<float>(texture.width) * prop->GetSpriteScale()
    , texture.height * prop->GetSpriteScale()
    , BLUE
    );
}

void GraphicsEngine::Render(Actor *actor)
{
    Vector2 wrld_pos = actor->GetWorldPosition();
    const auto& texture = GetTexture(actor->GetSpriteComponent().idle_texture_id_);
    Rectangle source{actor->GetFrame() * actor->GetWidth(), 0.f, actor->GetRightLeftDirection() * actor->GetWidth(), actor->GetHeight()};
    Rectangle dest{wrld_pos.x, wrld_pos.y, actor->GetSpriteScale() * actor->GetWidth(), actor->GetSpriteScale() * actor->GetHeight()};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
    DrawRectangleLines(wrld_pos.x
    , wrld_pos.y
    , static_cast<float>(texture.width) / actor->GetSpriteComponent().max_frame * actor->GetSpriteScale()
    , texture.height * actor->GetSpriteScale()
    , RED
    );
}

void GraphicsEngine::Render(Pawn *pawn)
{
    if (!(pawn->GetHealthComponent().is_alive))
    {
        return;
    }
    Vector2 wrld_pos = pawn->GetWorldPosition();
    Texture2D* texture;
    // still not working properly because velocity is always 0 at this point after end of game logic update
    if (Vector2Length(pawn->GetVelocity()) < 0.00001f)
        texture = &GetTexture(pawn->GetSpriteComponent().idle_texture_id_);
    else
        texture = &GetTexture(pawn->GetSpriteComponent().runing_texture_id_);
    Rectangle source{pawn->GetFrame() * pawn->GetWidth(), 0.f, pawn->GetRightLeftDirection() * pawn->GetWidth(), pawn->GetHeight()};
    Rectangle dest{wrld_pos.x, wrld_pos.y, pawn->GetSpriteScale() * pawn->GetWidth(), pawn->GetSpriteScale() * pawn->GetHeight()};
    DrawTexturePro(*texture, source, dest, Vector2{}, 0.f, WHITE);
    DrawRectangleLines(wrld_pos.x
    , wrld_pos.y
    , static_cast<float>(texture->width) / pawn->GetSpriteComponent().max_frame * pawn->GetSpriteScale()
    , texture->height * pawn->GetSpriteScale()
    , RED
    );
}

void GraphicsEngine::Render(BaseEnemy *enemy)
{
    if (!(enemy->GetHealthComponent().is_alive))
    {
        return;
    }
    Vector2 enemy_position_center = enemy->GetEnemyCenter();
    DrawCircleLines(enemy_position_center.x
            , enemy_position_center.y
            , enemy->GetSightRadius()
            , YELLOW
            );
    Vector2 wrld_pos = enemy->GetWorldPosition();
    Texture2D* texture;
    if (enemy->GetEnemyState() == EnemyState::IDLE)
        texture = &GetTexture(enemy->GetSpriteComponent().idle_texture_id_);
    else
        texture = &GetTexture(enemy->GetSpriteComponent().runing_texture_id_);
    Rectangle source{enemy->GetFrame() * enemy->GetWidth(), 0.f, enemy->GetRightLeftDirection() * enemy->GetWidth(), enemy->GetHeight()};
    Rectangle dest{wrld_pos.x, wrld_pos.y, enemy->GetSpriteScale() * enemy->GetWidth(), enemy->GetSpriteScale() * enemy->GetHeight()};
    DrawTexturePro(*texture, source, dest, Vector2{}, 0.f, WHITE);
    DrawRectangleLines(wrld_pos.x
    , wrld_pos.y
    , static_cast<float>(texture->width) / enemy->GetSpriteComponent().max_frame * enemy->GetSpriteScale()
    , texture->height * enemy->GetSpriteScale()
    , RED)
    ;
}

void GraphicsEngine::Render(BasePlayerCharacter *player)
{
    if (!player)
        return;
    Vector2 player_world_pos = player->GetWorldPosition();
    Texture2D* texture;
    if(player->_state != PlayerState::IDLE_STATE)
        texture = &GetTexture(player->GetSpriteComponent().runing_texture_id_);
    else
        texture = &GetTexture(player->GetSpriteComponent().idle_texture_id_);
    Rectangle source{player->GetFrame() * player->GetWidth(), 0.f, player->GetRightLeftDirection() * player->GetWidth(), player->GetHeight()};
    Rectangle dest{player_world_pos.x, player_world_pos.y, player->GetSpriteScale() * player->GetWidth(), player->GetSpriteScale() * player->GetHeight()};
    DrawTexturePro(*texture, source, dest, Vector2{}, 0.f, WHITE);
    
    if (!(player->GetWeaponTexture()))
        return;

    Texture2D* weapon_texture{player->GetWeaponTexture()};
    source = {0.0f, 0.0f, static_cast<float>((*weapon_texture).width) * player->GetRightLeftDirection(), static_cast<float>((*weapon_texture).height)};
    dest = {player_world_pos.x + player->GetWeaponOriginOffset().x, player_world_pos.y + player->GetWeaponOriginOffset().y, static_cast<float>((*weapon_texture).width) * player->GetWeaponScale(), static_cast<float>((*weapon_texture).height) * player->GetWeaponScale()};
    DrawTexturePro((*weapon_texture), source, dest, player->GetWeaponOrigin(), player->GetWeaponRotation(), WHITE);
    DrawRectangleLines(player->GetCollisionRectangle().x
    , player->GetCollisionRectangle().y
    , player->GetCollisionRectangle().width
    , player->GetCollisionRectangle().height
    , GREEN
    );
}

void GraphicsEngine::Render(ParticleSystem *particle_system)
{
    if (!particle_system)
        return;
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

void GraphicsEngine::RenderGameClock(float game_clock)
{
    static std::stringstream time_text;
    
    time_text << std::setw(2) << std::setfill('0') << int(game_clock) / 60;
    time_text << ":";
    time_text << std::setw(2) << std::setfill('0') << int(game_clock) % 60;
    DrawTextPro(GetFontDefault(), time_text.str().c_str(), Vector2{ window_width/2, 30 }, Vector2{ 0,0 }, 0.f, 24, 4, BLACK);
    
    time_text.str("");
    time_text.clear();
}
