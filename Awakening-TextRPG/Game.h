#pragma once

class Player;
class Inventory;
class World;
class Enemy;

class Game
{
    Player* player;
    Inventory* inventory;
    World* world;
    bool running;
public:
    Game();
    ~Game();
    void Run();
private:
    void MainMenu();
    void Explore();
    void ShowStatus() const;
    void ManageInventory();
    void Combat(Enemy* enemy);
    void Save();
    void Load();
};