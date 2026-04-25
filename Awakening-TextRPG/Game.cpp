#include "Game.h"
#include "Player.h"
#include "Inventory.h"
#include "World.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "FileManager.h"
#include <iostream>
#include <limits>
#include <memory>
using namespace std;

Game::Game()
    : player(nullptr), inventory(nullptr), world(nullptr), running(true)
{
    string name;
    cout << "Enter your knight's name: ";
    getline(cin, name);
    if (name.empty()) name = "Unnamed_Crusader";

    player = new Player(name);
    inventory = new Inventory();
    inventory->SetOwner(player);
    player->SetInventory(inventory);
    world = new World();

    inventory->AddItem(make_unique<Weapon>("Rusty_Sword", 2));
    inventory->AddItem(make_unique<Armor>("Worn_Mail", 1));
    inventory->AddItem(make_unique<Potion>("Minor_Healing", 20));
}

Game::~Game() 
{
    delete player;
    delete inventory;
    delete world;
}

void Game::Run() 
{
    while (running) 
    {
        MainMenu();
    }
}

void Game::MainMenu() 
{
    cout << "\n=== Awakening ===\n";
    cout << "1. Explore\n";
    cout << "2. Show Status\n";
    cout << "3. Inventory\n";
    cout << "4. Save Game\n";
    cout << "5. Load Game\n";
    cout << "6. Quit\n";
    cout << "Choose an option: ";

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        Explore();
        break;
    case 2:
        ShowStatus();
        break;
    case 3:
        ManageInventory();
        break;
    case 4:
        Save();
        break;
    case 5:
        Load();
        break;
    case 6:
        running = false;
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}

void Game::Explore() 
{
    world->HandleExploration(*player, *inventory);
    Enemy* enemy = world->GenerateRandomEnemy();
    cout << "You encounter " << enemy->GetName() << " (Level " << enemy->GetLevel() << ").\n";
    Combat(enemy);
    delete enemy;
}

void Game::ShowStatus() const 
{
    cout << "\n=== Status ===\n";
    cout << "Name: " << player->GetName() << "\n";
    cout << "Level: " << player->GetLevel() << "\n";
    cout << "Health: " << player->GetHealth() << "/" << player->GetMaxHealth() << "\n";
    cout << "Attack: " << player->GetAttack() << "\n";
    cout << "Defense: " << player->GetDefense() << "\n";
    cout << "Experience: " << player->GetExperience() << "/" << player->GetExperienceToLevel() << "\n";
}

void Game::ManageInventory() 
{
    bool managing = true;
    while (managing) 
    {
        cout << "\n=== Inventory ===\n";
        inventory->ListItems();
        cout << "Options:\n";
        cout << "1. Equip Weapon\n";
        cout << "2. Equip Armor\n";
        cout << "3. Use Potion\n";
        cout << "4. Back\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;
        if (choice == 4) 
        {
            managing = false;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "Enter item index: ";
        int index;
        cin >> index;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) 
        {
        case 1:
            inventory->EquipWeapon(index);
            break;
        case 2:
            inventory->EquipArmor(index);
            break;
        case 3:
            inventory->UsePotion(index);
            break;
        default:
            break;
        }
    }
}

void Game::Combat(Enemy* enemy)
{
    bool inCombat = true;
    while (inCombat && player->IsAlive() && enemy->IsAlive()) 
    {
        cout << "\n=== Combat ===\n";
        cout << player->GetName() << " HP: " << player->GetHealth() << "/" << player->GetMaxHealth() << "\n";
        cout << enemy->GetName() << " HP: " << enemy->GetHealth() << "/" << enemy->GetMaxHealth() << "\n";
        cout << "1. Attack\n";
        cout << "2. Use Potion\n";
        cout << "3. Attempt to Flee\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) 
        {
            int baseDamage = player->CalculateDamage();
            Weapon* w = inventory->GetEquippedWeapon();
            if (w) baseDamage += w->GetAttackBonus();
            int damage = baseDamage - enemy->GetDefense();
            if (damage < 0) damage = 0;
            cout << "You strike " << enemy->GetName() << " for " << damage << " damage.\n";
            enemy->TakeDamage(damage);
        }
        else if (choice == 2) 
        {
            inventory->ListItems();
            cout << "Enter potion index: ";
            int index;
            cin >> index;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inventory->UsePotion(index);
        }
        else if (choice == 3) 
        {
            cout << "You attempt to flee...\n";
            inCombat = false;
            break;
        }

        if (!enemy->IsAlive())
        {
            cout << "You defeated " << enemy->GetName() << "!\n";
            player->AddExperience(enemy->GetExperienceReward());
            cout << "You gained " << enemy->GetExperienceReward() << " experience.\n";
            break;
        }

        int enemyDamage = enemy->CalculateDamage() - player->GetDefense();
        Armor* a = inventory->GetEquippedArmor();
        if (a) enemyDamage -= a->GetDefenseBonus();
        if (enemyDamage < 0) enemyDamage = 0;
        cout << enemy->GetName() << " strikes you for " << enemyDamage << " damage.\n";
        player->TakeDamage(enemyDamage);

        if (!player->IsAlive())
        {
            cout << "You have fallen in battle...\n";
            running = false;
            break;
        }
    }
}

void Game::Save() {
    string filename = "savegame.txt";
    if (FileManager::SaveGame(filename, *player, *inventory)) 
    {
        cout << "Game saved to " << filename << "\n";
    }
    else
    {
        cout << "Failed to save game.\n";
    }
}

void Game::Load() {
    string filename = "savegame.txt";
    if (FileManager::LoadGame(filename, *player, *inventory)) 
    {
        inventory->SetOwner(player);
        player->SetInventory(inventory);
        cout << "Game loaded from " << filename << "\n";
    }
    else 
    {
        cout << "Failed to load game.\n";
    }
}