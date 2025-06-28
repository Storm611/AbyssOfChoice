#include "Shop.h"

Shop::Shop() {
    available_items_ = {
        {"Health Potion", 20, 0, 0, 0},

        {"Leather Cap", 5, 0, 0, 2},
        {"Iron Helmet", 10, 0, 0, 4},
        {"Steel Helm", 15, 0, 0, 6},
        {"Dragon Crown", 30, 2, 1, 8},

        {"Leather Vest", 15, 0, 0, 3},
        {"Chainmail", 25, 0, 0, 6},
        {"Plate Armor", 40, 0, 0, 9},
        {"Dragon Scale Mail", 50, 0, 0, 12},

        {"Leather Pants", 10, 0, 0, 2},
        {"Chain Leggings", 20, 0, 0, 4},
        {"Plate Greaves", 30, 0, 0, 6},
        {"Dragon Legplates", 40, 0, 0, 8},

        {"Iron Sword", 0, 6, 3, 0},
        {"Steel Axe", 0, 8, 5, 0},
        {"Mythril Blade", 0, 12, 7, 0},
        {"Dragon Slayer", 0, 15, 10, 2}
    };

    item_prices_ = {
        50,
        80,
        100,
        200,
        350,
        600,
        150,
        300,
        500,
        800,
        120,
        250,
        400,
        650,
        200,
        400,
        700,
        1000
    };
}

const std::vector<Shop::ItemStats>& Shop::GetAvailableItems() const {
    return available_items_;
}

int Shop::GetItemPrice(size_t index) const {
    return (index < item_prices_.size()) ? item_prices_[index] : -1;
}