#include "Enemy.h"
using namespace std;

Enemy::Enemy(const string& name, EnemyType type, int level, int maxHealth, int attack, int defense, int expReward)
    : Character(name, level, maxHealth, attack, defense), type(type), experienceReward(expReward) {
}

EnemyType Enemy::GetType() const 
{
    return type;
}

int Enemy::GetExperienceReward() const 
{
    return experienceReward;
}

int Enemy::CalculateDamage() const 
{
    return attack;
}