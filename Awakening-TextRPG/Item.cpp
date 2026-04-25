#include "Item.h"
using namespace std;

Item::Item(const string& name, ItemType type)
    : name(name), type(type) {
}

const string& Item::GetName() const 
{
    return name;
}

ItemType Item::GetType() const 
{
    return type;
}