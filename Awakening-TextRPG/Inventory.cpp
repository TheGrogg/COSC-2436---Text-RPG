#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Player.h"
#include <iostream>
using namespace std;

Inventory::Inventory()
    : equippedWeapon(nullptr), equippedArmor(nullptr), owner(nullptr) {
}

void Inventory::SetOwner(Player* player) {
    owner = player;
}

void Inventory::AddItem(unique_ptr<Item> item) {
    items.push_back(move(item));
}

void Inventory::ListItems() const {
    if (items.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i << ": " << items[i]->GetName();
        if (items[i].get() == equippedWeapon) cout << " (Equipped Weapon)";
        if (items[i].get() == equippedArmor) cout << " (Equipped Armor)";
        cout << "\n";
    }
}

void Inventory::EquipWeapon(int index) 
{
    if (index < 0 || index >= static_cast<int>(items.size())) return;
    Weapon* w = dynamic_cast<Weapon*>(items[index].get());
    if (w) {
        equippedWeapon = w;
        cout << "Equipped weapon: " << w->GetName() << "\n";
    }
}

void Inventory::EquipArmor(int index) 
{
    if (index < 0 || index >= static_cast<int>(items.size())) return;
    Armor* a = dynamic_cast<Armor*>(items[index].get());
    if (a) {
        equippedArmor = a;
        cout << "Equipped armor: " << a->GetName() << "\n";
    }
}

void Inventory::UsePotion(int index) 
{
    if (index < 0 || index >= static_cast<int>(items.size())) return;
    Potion* p = dynamic_cast<Potion*>(items[index].get());
    if (p && owner) 
    {
        cout << "Used potion: " << p->GetName() << "\n";
        owner->Heal(p->GetHealAmount());
        items.erase(items.begin() + index);
    }
}

Weapon* Inventory::GetEquippedWeapon() const 
{
    return equippedWeapon;
}

Armor* Inventory::GetEquippedArmor() const 
{
    return equippedArmor;
}

int Inventory::GetSize() const 
{
    return static_cast<int>(items.size());
}

Item* Inventory::GetItem(int index) const 
{
    if (index < 0 || index >= static_cast<int>(items.size())) return nullptr;
    return items[index].get();
}

void Inventory::Clear() 
{
    items.clear();
    equippedWeapon = nullptr;
    equippedArmor = nullptr;
}