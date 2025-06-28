#include "playerinventory.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

PlayerInventory::ItemStats::ItemStats(const std::string& n, int hp, int dmg,
    int hard_dmg, int def)
    : name(n),
    hp_bonus(hp),
    damage_bonus(dmg),
    hard_damage_bonus(hard_dmg),
    defense_bonus(def) {
}

void PlayerInventory::ItemStats::SaveToStream(std::ostream& os) const {
    std::string save_name = name;
    std::replace(save_name.begin(), save_name.end(), ' ', '_');
    os << save_name << " "
        << hp_bonus << " "
        << damage_bonus << " "
        << hard_damage_bonus << " "
        << defense_bonus;
}

void PlayerInventory::ItemStats::LoadFromStream(std::istream& is) {
    is >> name;
    std::replace(name.begin(), name.end(), '_', ' ');
    is >> hp_bonus >> damage_bonus >> hard_damage_bonus >> defense_bonus;
}

PlayerInventory::PlayerInventory() {
    // Initialize empty slots
    equipped_items_[ItemType::HELMET] = ItemStats();
    equipped_items_[ItemType::CHEST] = ItemStats();
    equipped_items_[ItemType::LEGS] = ItemStats();
    equipped_items_[ItemType::WEAPON] = ItemStats();
}

void PlayerInventory::EquipItem(ItemType slot, const ItemStats& item) {
    equipped_items_[slot] = item;
}

void PlayerInventory::UnequipItem(ItemType slot) {
    equipped_items_[slot] = ItemStats();
}

const PlayerInventory::ItemStats& PlayerInventory::GetItem(ItemType slot) const {
    return equipped_items_.at(slot);
}

void PlayerInventory::ShowInventory() const {
    std::cout << "\n=== INVENTORY ===\n";
    std::cout << "1. Helmet: " << equipped_items_.at(ItemType::HELMET).name << "\n";
    std::cout << "2. Chest: " << equipped_items_.at(ItemType::CHEST).name << "\n";
    std::cout << "3. Legs: " << equipped_items_.at(ItemType::LEGS).name << "\n";
    std::cout << "4. Weapon: " << equipped_items_.at(ItemType::WEAPON).name << "\n";
}

std::string PlayerInventory::SlotToString(ItemType slot) {
    switch (slot) {
    case ItemType::HELMET: return "Helmet";
    case ItemType::CHEST: return "Chest";
    case ItemType::LEGS: return "Legs";
    case ItemType::WEAPON: return "Weapon";
    default: return "Unknown";
    }
}

PlayerInventory::ItemStats PlayerInventory::GetTotalBonuses() const {
    ItemStats total;
    for (const auto& item : equipped_items_) {
        total.hp_bonus += item.second.hp_bonus;
        total.damage_bonus += item.second.damage_bonus;
        total.hard_damage_bonus += item.second.hard_damage_bonus;
        total.defense_bonus += item.second.defense_bonus;
    }
    return total;
}

void PlayerInventory::SaveToFile(std::ofstream& file) const {
    for (const auto& slot_item : equipped_items_) {
        file << static_cast<int>(slot_item.first) << " ";
        slot_item.second.SaveToStream(file);
        file << "\n";
    }
    file << "END_INVENTORY\n";
}

void PlayerInventory::LoadFromFile(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        if (line == "END_INVENTORY") break;

        std::istringstream iss(line);
        int type;
        iss >> type;

        ItemStats loaded_item;
        loaded_item.LoadFromStream(iss);

        equipped_items_[static_cast<ItemType>(type)] = loaded_item;
    }
}