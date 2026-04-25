#pragma once
#include "Character.h"

enum class EnemyType 
{
    Orc,
    Shaman,
    Warlord
};

class Enemy : public Character 
{
    EnemyType type;
    int experienceReward;
public:
    Enemy(const std::string& name, EnemyType type, int level, int maxHealth, int attack, int defense, int expReward);
    EnemyType GetType() const;
    int GetExperienceReward() const;
    int CalculateDamage() const override;
};