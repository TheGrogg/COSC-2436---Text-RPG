#include "Player.h"
#include "Inventory.h"
using namespace std;

Player::Player(const string& name)
    : Character(name, 1, 100, 10, 5), experience(0), experienceToLevel(100), inventory(nullptr){
}

void Player::SetInventory(Inventory* inv) 
{
    inventory = inv;
}

int Player::GetExperience() const 
{
    return experience;
}

int Player::GetExperienceToLevel() const 
{
    return experienceToLevel;
}

void Player::AddExperience(int amount) 
{
    experience += amount;
    while (experience >= experienceToLevel) 
    {
        experience -= experienceToLevel;
        LevelUp();
    }
}

void Player::LevelUp()
{
    level++;
    maxHealth += 20;
    health = maxHealth;
    attack += 5;
    defense += 3;
    experienceToLevel += 50;
}

void Player::SetProgress(int exp, int expToLevel)
{
    experience = exp;
    experienceToLevel = expToLevel;
}

int Player::CalculateDamage() const 
{
    return attack;
}