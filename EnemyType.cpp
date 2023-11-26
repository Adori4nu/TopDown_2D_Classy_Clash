#include "EnemyType.hpp"

#include "BaseEnemy.hpp"

BaseEnemy *EnemyType::newEnemy()
{
    return new BaseEnemy(*this); 
}
