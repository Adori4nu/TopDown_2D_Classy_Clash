#include "EnemySpawner.hpp"
#include "BaseEnemy.hpp"
#include "Game.hpp"
#include "GraphicsEngine.hpp"

void EnemySpawner::tick(float delta_time)
{
    const auto& game_time {GetGameClock()};
    auto& Graphics_Engine_ = GraphicsEngine::Get();

    for (auto &&wave_data : wave_spawns_data)
    {
        if (wave_data.starting_time == wave_data.end_time
            && game_time >= wave_data.starting_time
            && wave_data.mob_count > 0
            )
        {
            while(wave_data.mob_count > 0)
            {
                BaseEnemy* mob = wave_data.mob.newEnemy();
                mob->SetParticleSystem(GetParticleSystem());
                mob->SetWorld(GetWorld());
        //     for(auto prop : props)
        //         while(CheckCollisionRecs(enemy->GetCollisionRectangle(), prop->GetCollisionRectangle()))
        //         {
        //             enemy->SetWorldPosition(Vector2{(Random::Int(12,48))*32.f, (Random::Int(12,48))*32.f});
        //         }
                mob->SetWorldPosition(mob->SetRandomPositionOnCircle(GetPlayerCharacter().GetWorldPosition()));
                mob->SetTarget(&GetPlayerCharacter());
                mob->SetWidthAndHeight();
                GetEnemyPool().emplace_back(*mob);

                Graphics_Engine_.AddGameObject(&GetEnemyPool().back());

                --wave_data.mob_count;
            }
        }
        if (game_time >= wave_data.starting_time && game_time <= wave_data.end_time)
        {
            wave_data.spawn_wait_clock += delta_time;
            if (wave_data.spawn_wait_clock >= wave_data.mob_spawn_delay)
            {
                wave_data.spawn_wait_clock = {};
                if (wave_data.mob_count > 0)
                {
                    BaseEnemy* mob = wave_data.mob.newEnemy();
                    mob->SetParticleSystem(GetParticleSystem());
                    mob->SetWorld(GetWorld());
                    
                    mob->SetWorldPosition(mob->SetRandomPositionOnCircle(GetPlayerCharacter().GetWorldPosition()));
                    mob->SetTarget(&GetPlayerCharacter());
                    mob->SetWidthAndHeight();
                    GetEnemyPool().emplace_back(*mob);

                    Graphics_Engine_.AddGameObject(&GetEnemyPool().back());

                    --wave_data.mob_count;
                }
            }
        }
    }
    
}

void EnemySpawner::AddWave(EnemyWave wave_data)
{
    wave_spawns_data.emplace_back(wave_data);
}
