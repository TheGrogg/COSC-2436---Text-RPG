#pragma once
#include <string>

class Player;
class Inventory;

class FileManager 
{
public:
    static bool SaveGame(const std::string& filename, const Player& player, const Inventory& inventory);
    static bool LoadGame(const std::string& filename, Player& player, Inventory& inventory);
};