#include "World.h"
#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include <iostream>
#include <memory>
#include <chrono>
using namespace std;

World::World() 
{
    rng.seed(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
}

Enemy* World::GenerateRandomEnemy() 
{
    uniform_int_distribution<int> typeDist(0, 2);
    int t = typeDist(rng);
    EnemyType type = EnemyType::Orc;
    string name = "Orc_Grunt";
    int level = 1;
    int hp = 50;
    int atk = 8;
    int def = 3;
    int exp = 50;

    if (t == 1) 
    {
        type = EnemyType::Shaman;
        name = "Orc_Shaman";
        level = 2;
        hp = 70;
        atk = 10;
        def = 4;
        exp = 80;
    }
    else if (t == 2) 
    {
        type = EnemyType::Warlord;
        name = "Orc_Warlord";
        level = 3;
        hp = 100;
        atk = 14;
        def = 6;
        exp = 120;
    }

    return new Enemy(name, type, level, hp, atk, def, exp);
}

void World::HandleExploration(Player& player, Inventory& inventory) 
{
    uniform_int_distribution<int> eventDist(0, 2);
    int e = eventDist(rng);
    if (e == 0) {
        cout << "You find a quiet clearing. You rest and recover some health.\n";
        player.Heal(20);
    }
    else if (e == 1) {
        cout << "You discover a forgotten cache of equipment.\n";
        uniform_int_distribution<int> lootDist(0, 2);
        int l = lootDist(rng);
        if (l == 0) {
            inventory.AddItem(make_unique<Weapon>("Crusader_Blade", 5));
            cout << "You found a weapon: Crusader_Blade.\n";
        }
        else if (l == 1) 
        {
            inventory.AddItem(make_unique<Armor>("Knights_Plate", 4));
            cout << "You found armor: Knights_Plate.\n";
        }
        else 
        {
            inventory.AddItem(make_unique<Potion>("Healing_Draught", 30));
            cout << "You found a potion: Healing_Draught.\n";
        }
    }
    else 
    {
        cout << "The air grows tense. You sense danger nearby.\n";
    }
}