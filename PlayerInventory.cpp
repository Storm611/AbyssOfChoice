#include "PlayerInventory.h"

Inventory::Inventory() {
    for (int i = 0; i < ITEM_TYPE_COUNT; ++i) {
        inventory[static_cast<ItemType>(i)] = ItemStats();
    }
}

void Inventory::validateSlot(ItemType slot) const {
    if (slot < 0 || slot >= ITEM_TYPE_COUNT) {
        throw std::out_of_range("Invalid inventory slot");
    }
}

void Inventory::equipItem(ItemType slot, const ItemStats& item) {
    validateSlot(slot);
    inventory[slot] = item;
}

void Inventory::unequipItem(ItemType slot) {
    validateSlot(slot);
    inventory[slot] = ItemStats();
}

const Inventory::ItemStats& Inventory::getItem(ItemType slot) const {
    validateSlot(slot);
    return inventory.at(slot);
}

int Inventory::getTotalHpBonus() const {
    int total = 0;
    for (const auto& entry : inventory) {
        total += entry.second.hp_bonus;
    }
    return total;
}

int Inventory::getTotalDamageBonus() const {
    int total = 0;
    for (const auto& entry : inventory) {
        total += entry.second.damage_bonus;
    }
    return total;
}

int Inventory::getTotalHardDamageBonus() const {
    int total = 0;
    for (const auto& entry : inventory) {
        total += entry.second.hard_damage_bonus;
    }
    return total;
}

int Inventory::getTotalDefenseBonus() const {
    int total = 0;
    for (const auto& entry : inventory) {
        total += entry.second.defense_bonus;
    }
    return total;
}

void Inventory::showInventory() const {
    std::cout << "\n=== Inventory ===" << std::endl;
    for (const auto& entry : inventory) {
        std::cout << slotToString(entry.first) << ": " << entry.second.name
            << " (HP: +" << entry.second.hp_bonus
            << ", DMG: +" << entry.second.damage_bonus
            << ", Hard DMG: +" << entry.second.hard_damage_bonus
            << ", DEF: +" << entry.second.defense_bonus << ")" << std::endl;
    }
    std::cout << "================\n" << std::endl;
}

std::string Inventory::slotToString(ItemType slot) {
    switch (slot) {
    case HELMET: return "Helmet";
    case CHESTPLATE: return "Chestplate";
    case LEGGINGS: return "Leggings";
    case SWORD: return "Sword";
    case ACCESSORY: return "Accessory";
    default: return "Unknown";
    }
}