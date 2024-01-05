#pragma once

#include <iostream>

class HealthComponent
{
public:
    HealthComponent(int max_health = 100)
    : _max_health(max_health)
    , _current_health(max_health)
     {};

    // HealthComponent(const HealthComponent&) = delete;
    // HealthComponent& operator=(HealthComponent&) = delete;

    int TakeDamage(int damage);
    
    __forceinline int GetHealth() const { return _current_health; };

    __forceinline void SetMaxHealth(int new_max_health) { _max_health = new_max_health; };
    __forceinline void SetHealth(int health) { _current_health = health; };
    bool IsAlive() const { return is_alive; };
    void SetIsAlive(bool alive)
    {
        is_alive = alive;
    };
   
    int _max_health{};
    int _current_health{};
    bool is_alive{true};
protected:

private:
};