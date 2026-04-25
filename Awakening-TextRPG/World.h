#pragma once
#include <random>

class Enemy;
class Player;
class Inventory;

class World
{
    std::mt19937 rng;
public:
    World();
    Enemy* GenerateRandomEnemy();
    void HandleExploration(Player& player, Inventory& inventory);
};