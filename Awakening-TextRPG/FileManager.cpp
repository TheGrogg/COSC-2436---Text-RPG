#include "FileManager.h"
#include "Player.h"
#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include <fstream>
#include <iostream>
#include <memory>
using namespace std;

bool FileManager::SaveGame(const string& filename, const Player& player, const Inventory& inventory)
{
    ofstream out(filename);
    if (!out) return false;

    out << player.GetName() << "\n";
    out << player.GetLevel() << " "
        << player.GetHealth() << " "
        << player.GetMaxHealth() << " "
        << player.GetAttack() << " "
        << player.GetDefense() << " "
        << player.GetExperience() << " "
        << player.GetExperienceToLevel() << "\n";

    out << inventory.GetSize() << "\n";
    for (int i = 0; i < inventory.GetSize(); ++i) 
    {
        Item* item = inventory.GetItem(i);
        if (!item) continue;
        ItemType type = item->GetType();
        if (type == ItemType::Weapon) 
        {
            Weapon* w = dynamic_cast<Weapon*>(item);
            out << "Weapon " << w->GetName() << " " << w->GetAttackBonus() << "\n";
        }
        else if (type == ItemType::Armor) 
        {
            Armor* a = dynamic_cast<Armor*>(item);
            out << "Armor " << a->GetName() << " " << a->GetDefenseBonus() << "\n";
        }
        else if (type == ItemType::Potion) 
        {
            Potion* p = dynamic_cast<Potion*>(item);
            out << "Potion " << p->GetName() << " " << p->GetHealAmount() << "\n";
        }
    }

    return true;
}

bool FileManager::LoadGame(const string& filename, Player& player, Inventory& inventory) 
{
    ifstream in(filename);
    if (!in) return false;

    string nameLine;
    getline(in, nameLine);

    int level, health, maxHealth, attack, defense, exp, expToLevel;
    in >> level >> health >> maxHealth >> attack >> defense >> exp >> expToLevel;

    player.SetStats(level, maxHealth, health, attack, defense);
    player.SetProgress(exp, expToLevel);

    int itemCount;
    in >> itemCount;

    inventory.Clear();

    for (int i = 0; i < itemCount; ++i)
    {
        string typeStr;
        in >> typeStr;
        if (typeStr == "Weapon") 
        {
            string wname;
            int bonus;
            in >> wname >> bonus;
            inventory.AddItem(make_unique<Weapon>(wname, bonus));
        }
        else if (typeStr == "Armor")
        {
            string aname;
            int bonus;
            in >> aname >> bonus;
            inventory.AddItem(make_unique<Armor>(aname, bonus));
        }
        else if (typeStr == "Potion") 
        {
            string pname;
            int heal;
            in >> pname >> heal;
            inventory.AddItem(make_unique<Potion>(pname, heal));
        }
    }

    return true;
}