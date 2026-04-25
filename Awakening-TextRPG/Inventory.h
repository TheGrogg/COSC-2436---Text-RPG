#pragma once
#include <vector>
#include <memory>

class Item;
class Weapon;
class Armor;
class Potion;
class Player;

class Inventory 
{
    std::vector<std::unique_ptr<Item>> items;
    Weapon* equippedWeapon;
    Armor* equippedArmor;
    Player* owner;
public:
    Inventory();
    void SetOwner(Player* player);
    void AddItem(std::unique_ptr<Item> item);
    void ListItems() const;
    void EquipWeapon(int index);
    void EquipArmor(int index);
    void UsePotion(int index);
    Weapon* GetEquippedWeapon() const;
    Armor* GetEquippedArmor() const;
    int GetSize() const;
    Item* GetItem(int index) const;
    void Clear();
};