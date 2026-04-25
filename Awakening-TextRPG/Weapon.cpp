#include "Weapon.h"
using namespace std;

Weapon::Weapon(const string& name, int attackBonus)
    : Item(name, ItemType::Weapon), attackBonus(attackBonus) {
}

int Weapon::GetAttackBonus() const 
{
    return attackBonus;
}