#pragma once
#include <string>
#include <map>
#include <iostream>

class PlayerInventory {
public:
    enum class ItemType { HELMET, CHEST, LEGS, WEAPON };

    struct ItemStats {
        std::string name;
        int hp_bonus;
        int damage_bonus;
        int hard_damage_bonus;
        int defense_bonus;

        ItemStats(const std::string& n = "None", int hp = 0, int dmg = 0, int hard_dmg = 0, int def = 0)
            : name(n), hp_bonus(hp), damage_bonus(dmg), hard_damage_bonus(hard_dmg), defense_bonus(def) {
        }
    };

private:
    std::map<ItemType, ItemStats> equippedItems;

public:
    PlayerInventory() {
        // Инициализация пустых слотов
        equippedItems[ItemType::HELMET] = ItemStats();
        equippedItems[ItemType::CHEST] = ItemStats();
        equippedItems[ItemType::LEGS] = ItemStats();
        equippedItems[ItemType::WEAPON] = ItemStats();
    }

    void equipItem(ItemType slot, const ItemStats& item) {
        equippedItems[slot] = item;
    }

    void unequipItem(ItemType slot) {
        equippedItems[slot] = ItemStats();
    }

    const ItemStats& getItem(ItemType slot) const {
        return equippedItems.at(slot);
    }

    void showInventory() const {
        std::cout << "\n=== INVENTORY ===\n";
        std::cout << "1. Helmet: " << equippedItems.at(ItemType::HELMET).name << "\n";
        std::cout << "2. Chest: " << equippedItems.at(ItemType::CHEST).name << "\n";
        std::cout << "3. Legs: " << equippedItems.at(ItemType::LEGS).name << "\n";
        std::cout << "4. Weapon: " << equippedItems.at(ItemType::WEAPON).name << "\n";
    }

    static std::string slotToString(ItemType slot) {
        switch (slot) {
        case ItemType::HELMET: return "Helmet";
        case ItemType::CHEST: return "Chest";
        case ItemType::LEGS: return "Legs";
        case ItemType::WEAPON: return "Weapon";
        default: return "Unknown";
        }
    }

    // Метод для подсчета суммарных бонусов
    ItemStats getTotalBonuses() const {
        ItemStats total;
        for (const auto& item : equippedItems) {
            total.hp_bonus += item.second.hp_bonus;
            total.damage_bonus += item.second.damage_bonus;
            total.hard_damage_bonus += item.second.hard_damage_bonus;
            total.defense_bonus += item.second.defense_bonus;
        }
        return total;
    }
};