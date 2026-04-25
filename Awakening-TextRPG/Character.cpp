#include "Character.h"
using namespace std;

Character::Character(const string& name, int level, int maxHealth, int attack, int defense)
    : name(name), level(level), maxHealth(maxHealth), health(maxHealth), attack(attack), defense(defense) {
}

const string& Character::GetName() const 
{
    return name;
}

int Character::GetLevel() const 
{
    return level;
}

int Character::GetHealth() const 
{
    return health;
}

int Character::GetMaxHealth() const 
{
    return maxHealth;
}

int Character::GetAttack() const 
{
    return attack;
}

int Character::GetDefense() const 
{
    return defense;
}

bool Character::IsAlive() const 
{
    return health > 0;
}

void Character::TakeDamage(int amount) 
{
    health -= amount;
    if (health < 0) health = 0;
}

void Character::Heal(int amount) 
{
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Character::SetStats(int lvl, int maxHp, int hp, int atk, int def) 
{
    level = lvl;
    maxHealth = maxHp;
    health = hp;
    attack = atk;
    defense = def;
}