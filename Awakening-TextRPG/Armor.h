#pragma once
#include "Item.h"

class Armor : public Item 
{
    int defenseBonus;
public:
    Armor(const std::string& name, int defenseBonus);
    int GetDefenseBonus() const;
};