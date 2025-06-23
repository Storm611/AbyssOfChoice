// Shop.h
#pragma once
#include "PlayerInventory.h"
#include <vector>

class Shop {
public:
    using ItemStats = PlayerInventory::ItemStats;
    using ItemType = PlayerInventory::ItemType;

private:
    std::vector<ItemStats> availableItems = {
        // Шлемы
        {"Iron Helmet", 20, 0, 0, 10},
        {"Steel Helmet", 30, 0, 0, 15},

        // Нагрудники
        {"Leather Armor", 40, 0, 0, 15},
        {"Chainmail", 60, 0, 0, 25},
        {"Plate Armor", 80, 0, 0, 35},

        // Поножи
        {"Leather Pants", 20, 0, 0, 10},
        {"Steel Greaves", 40, 0, 0, 20},

        // Оружие
        {"Iron Sword", 0, 15, 5, 0},
        {"Steel Sword", 0, 25, 10, 0},
        {"Two-Handed Axe", 0, 30, 15, 0},

        // Расходники (здоровье будет обрабатываться отдельно)
        {"Health Potion", 0, 0, 0, 0}
    };

    std::vector<int> itemPrices = {
        150, 250,   // Шлемы
        200, 350, 500, // Нагрудники
        150, 300,   // Поножи
        300, 500, 600, // Оружие
        50          // Зелья
    };

public:
    const std::vector<ItemStats>& getAvailableItems() const {
        return availableItems;
    }

    int getItemPrice(size_t index) const {
        return (index < itemPrices.size()) ? itemPrices[index] : 0;
    }
};