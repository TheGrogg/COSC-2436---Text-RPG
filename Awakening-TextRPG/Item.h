#pragma once
#include <string>

enum class ItemType 
{
    Weapon,
    Armor,
    Potion
};

class Item 
{
protected:
    std::string name;
    ItemType type;
public:
    Item(const std::string& name, ItemType type);
    virtual ~Item() = default;

    const std::string& GetName() const;
    ItemType GetType() const;
};
