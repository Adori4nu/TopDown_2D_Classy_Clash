#include "HealthComponent.hpp"

int HealthComponent::TakeDamage(int damage)
{
    _current_health -= damage;
    if (_current_health <= 0)
    {
        SetIsAlive(false);
        return 1;
    }
    return 0;
}