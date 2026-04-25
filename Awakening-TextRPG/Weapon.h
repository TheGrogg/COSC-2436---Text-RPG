#pragma once
#include "Item.h"

class Weapon : public Item 
{
    int attackBonus;
public:
    Weapon(const std::string& name, int attackBonus);
    int GetAttackBonus() const;
};