#include "Armor.h"
using namespace std;

Armor::Armor(const string& name, int defenseBonus)
    : Item(name, ItemType::Armor), defenseBonus(defenseBonus) {
}

int Armor::GetDefenseBonus() const 
{
    return defenseBonus;
}