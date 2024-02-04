#include "Item.hpp"
#include "gameConstants.hpp"
#include "helperFunctions.hpp"
#include "Random.hpp"

#include <vector>

std::vector<Item> ItemPool{};

Item *AddItem(const char *name, int texture_id, ItemType type)
{
    int id{int(ItemPool.size())};

    ItemPool.emplace_back(Item{ id, std::string(name), texture_id });
    return GetItem(id);
}

Item *GetItem(int id)
{
    if ( id < 0 || id >= ItemPool.size() )
        return nullptr;
    
    return &ItemPool[id];
}

int GetRandomItem(int except)
{
    int id{ -1 };
    while (id == -1)
    {
        int index{Random::Int(0, int(ItemPool.size()) - 1 )};
        id = ItemPool[index]._id;
        if (id == except)
            id = -1;
    }
    
    return id;
}

void SetupDefaultItems()
{
    auto* item{ AddItem("Sword", TextureIDs::Equipment::basic_sword_texture, ItemType::Weapon) };
    item->attack.min_damage = 4;
    item->attack.max_damage = 6;
    item->attack.range = 0.33f;

    item = AddItem("Red Sword", TextureIDs::Equipment::basic_sword_texture, ItemType::Weapon);
    item->attack.min_damage = 6;
    item->attack.max_damage = 8;
    item->attack.range = 1.33f;
}
