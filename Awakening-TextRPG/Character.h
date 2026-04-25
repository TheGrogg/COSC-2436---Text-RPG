#pragma once
#include <string>

class Character 
{
protected:
    std::string name;
    int level;
    int maxHealth;
    int health;
    int attack;
    int defense;
public:
    Character(const std::string& name, int level, int maxHealth, int attack, int defense);
    virtual ~Character() = default;

    const std::string& GetName() const;
    int GetLevel() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetDefense() const;
    bool IsAlive() const;

    void TakeDamage(int amount);
    void Heal(int amount);
    void SetStats(int level, int maxHealth, int health, int attack, int defense);

    virtual int CalculateDamage() const = 0;
};