#include "Potion.h"
using namespace std;

Potion::Potion(const string& name, int healAmount)
    : Item(name, ItemType::Potion), healAmount(healAmount) {
}

int Potion::GetHealAmount() const 
{
    return healAmount;
}