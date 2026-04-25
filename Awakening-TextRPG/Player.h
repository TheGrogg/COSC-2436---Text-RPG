#pragma once
#include "Character.h"

class Inventory;

class Player : public Character 
{
    int experience;
    int experienceToLevel;
    Inventory* inventory;
public:
    Player(const std::string& name);
    void SetInventory(Inventory* inv);
    int GetExperience() const;
    int GetExperienceToLevel() const;
    void AddExperience(int amount);
    void LevelUp();
    void SetProgress(int experience, int experienceToLevel);
    int CalculateDamage() const override;
};