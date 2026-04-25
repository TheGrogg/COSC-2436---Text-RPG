#pragma once
#include "Item.h"

class Potion : public Item 
{
    int healAmount;
public:
    Potion(const std::string& name, int healAmount);
    int GetHealAmount() const;
};