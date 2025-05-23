#pragma once
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

class Inventory {
public:
    enum ItemType {
        HELMET = 0,
        CHESTPLATE,
        LEGGINGS,
        SWORD,
        ACCESSORY,
        ITEM_TYPE_COUNT
    };

    struct ItemStats {
        std::string name;
        int hp_bonus;
        int damage_bonus;
        int hard_damage_bonus;
        int defense_bonus;

        ItemStats(const std::string& n = "None",
            int hp = 0, int dmg = 0,
            int hard_dmg = 0, int def = 0)
            : name(n), hp_bonus(hp), damage_bonus(dmg),
            hard_damage_bonus(hard_dmg), defense_bonus(def) {}
    };

    Inventory();

    void equipItem(ItemType slot, const ItemStats& item);
    void unequipItem(ItemType slot);
    const ItemStats& getItem(ItemType slot) const;

    int getTotalHpBonus() const;
    int getTotalDamageBonus() const;
    int getTotalHardDamageBonus() const;
    int getTotalDefenseBonus() const;

    void showInventory() const;
    static std::string slotToString(ItemType slot);

private:
    void validateSlot(ItemType slot) const;
    std::map<ItemType, ItemStats> inventory;
};