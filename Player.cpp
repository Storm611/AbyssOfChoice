
#include "player.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "XP.h"
Player::Player(int hp, int damage, int hard_damage, int defense, int health_potion)
    : Character(hp, damage, hard_damage, defense),
    level_(1),
    base_max_hp_(hp),
    base_damage_(damage),
    base_hard_damage_(hard_damage),
    base_defense_(defense),
    money_(0),
    health_potion_(health_potion) {
    RecalculateStats();
}

void Player::GainExperience(int exp) {
    xp_.addExperience(exp);
    while (xp_.checkLevelUp()) {
        xp_.levelUp();
        LevelUp();
    }
}
int Player::GetHp() const { return HP; }
int Player::GetLevel() const { return level_; }

int Player::GetMaxHp() const { return max_hp_; }

int Player::GetBaseMaxHp() const { return base_max_hp_; }

void Player::Heal(int amount) {
    HP += amount;
    if (HP > max_hp_) {
        HP = max_hp_;
    }
    std::cout << "Healed for " << amount << " HP. Now: " << HP << "/" << max_hp_ << "\n";
}

bool Player::UseHealthPotion() {
    if (health_potion_ > 0) {
        int heal_amount = (GetMaxHp() * 40) / 100;
        std::cout << "Attempting to heal for " << heal_amount << " HP...\n";
        Heal(heal_amount);
        health_potion_--;
        std::cout << "Used health potion. HP: " << HP << "/" << max_hp_ << "\n";
        return true;
    }
    std::cout << "No health potions left!\n";
    return false;
}

void Player::GainMoney(int amount) {
    money_ += amount;
    std::cout << "Obtained " << amount << " gold. Total: " << money_ << "\n";
}

int Player::GetMoney() const { return money_; }

void Player::EquipItem(PlayerInventory::ItemType slot, const std::string& name,
    int hp_bonus, int damage_bonus,
    int hard_damage_bonus, int defense_bonus) {
    UnequipItem(slot);
    PlayerInventory::ItemStats new_item(name, hp_bonus, damage_bonus,
        hard_damage_bonus, defense_bonus);
    inventory_.EquipItem(slot, new_item);
    ApplyItemBonuses(new_item, true);
    std::cout << "Equipped " << name << " ("
        << PlayerInventory::SlotToString(slot) << ")\n";
    Heal(GetMaxHp());
}

void Player::UnequipItem(PlayerInventory::ItemType slot) {
    const auto& item = inventory_.GetItem(slot);
    if (item.name != "None") {
        ApplyItemBonuses(item, false);
        inventory_.UnequipItem(slot);
        std::cout << "Unequipped " << item.name << "\n";
    }
}

void Player::ShowInventory() const {
    std::cout << "\n=== INVENTORY ===\n";
    std::cout << "Gold: " << money_ << "\n";
    std::cout << "Health potions: " << health_potion_ << "\n\n";
    inventory_.ShowInventory();

    auto bonuses = inventory_.GetTotalBonuses();
    std::cout << "\nTotal bonuses:\n";
    std::cout << "HP: +" << bonuses.hp_bonus << "\n";
    std::cout << "Damage: +" << bonuses.damage_bonus << "\n";
    std::cout << "Heavy Damage: +" << bonuses.hard_damage_bonus << "\n";
    std::cout << "Defense: +" << bonuses.defense_bonus << "\n";
}

void Player::ShowStats() const {
    std::cout << "\n=== PLAYER STATS ===\n";
    std::cout << "Level: " << level_ << "\n";
    std::cout << "HP: " << HP << "/" << max_hp_ << "\n";
    std::cout << "Damage: " << Damage << " (+" << Damage - base_damage_ << ")\n";
    std::cout << "Heavy Damage: " << Hard_Damage << " (+"
        << Hard_Damage - base_hard_damage_ << ")\n";
    std::cout << "Defense: " << Defense << " (+" << Defense - base_defense_ << ")\n";
}

void Player::AddHealthPotion(int count) {
    health_potion_ += count;
}

void Player::BuyItem(const PlayerInventory::ItemStats& item, int price) {
    if (money_ >= price) {
        money_ -= price;

        if (item.name == "Health Potion") {
            health_potion_++;
            std::cout << "Bought health potion!\n";
        }
        else {
            PlayerInventory::ItemType slot;
            if (item.name.find("Helmet") != std::string::npos) {
                slot = PlayerInventory::ItemType::HELMET;
            }
            else if (item.name.find("Armor") != std::string::npos ||
                item.name.find("Chainmail") != std::string::npos) {
                slot = PlayerInventory::ItemType::CHEST;
            }
            else if (item.name.find("Pants") != std::string::npos ||
                item.name.find("Greaves") != std::string::npos) {
                slot = PlayerInventory::ItemType::LEGS;
            }
            else {
                slot = PlayerInventory::ItemType::WEAPON;
            }

            EquipItem(slot, item.name, item.hp_bonus,
                item.damage_bonus, item.hard_damage_bonus, item.defense_bonus);
        }
    }
    else {
        std::cout << "Not enough gold!\n";
    }
}

void Player::SaveGame() {
    std::ofstream player_file("player.sav");
    player_file << level_ << " "
        << base_max_hp_ << " "
        << base_damage_ << " "
        << base_hard_damage_ << " "
        << base_defense_ << " "
        << money_ << " "
        << health_potion_ << " "
        << HP << "\n";
    player_file.close();

    std::ofstream inv_file("inventory.sav");
    inventory_.SaveToFile(inv_file);
    inv_file.close();

    std::ofstream xp_file("xp.sav");
    xp_.saveToFile(xp_file);
    xp_file.close();
}

void Player::LoadGame() {
    std::ifstream player_file("player.sav");
    if (player_file) {
        player_file >> level_
            >> base_max_hp_
            >> base_damage_
            >> base_hard_damage_
            >> base_defense_
            >> money_
            >> health_potion_
            >> HP;
        player_file.close();
    }

    std::ifstream inv_file("inventory.sav");
    if (inv_file) {
        inventory_.LoadFromFile(inv_file);
        inv_file.close();
    }

    std::ifstream xp_file("xp.sav");
    if (xp_file) {
        xp_.loadFromFile(xp_file);
        xp_file.close();
    }

    RecalculateStats();
}

void Player::LevelUp() {
    level_++;
    base_max_hp_ += 10 + level_;
    base_damage_ += 2 + level_ / 2;
    base_hard_damage_ += 3 + level_ / 2;
    base_defense_ += 1 + level_ / 3;

    RecalculateStats();
    HP = max_hp_;

    std::cout << "\nLEVEL UP! (" << level_ << ")\n";
    std::cout << "HP: " << max_hp_ << " (+" << 10 + level_ << ")\n";
    std::cout << "Damage: " << Damage << " (+" << 2 + level_ / 2 << ")\n";
    std::cout << "Heavy Damage: " << Hard_Damage << " (+" << 3 + level_ / 2 << ")\n";
    std::cout << "Defense: " << Defense << " (+" << 1 + level_ / 3 << ")\n";
}

void Player::ApplyItemBonuses(const PlayerInventory::ItemStats& item, bool equip) {
    int modifier = 0.5;
    base_max_hp_ += modifier * item.hp_bonus;
    base_damage_ += modifier * item.damage_bonus;
    base_hard_damage_ += modifier * item.hard_damage_bonus;
    base_defense_ += modifier * item.defense_bonus;
    RecalculateStats();
}

void Player::RecalculateStats() {
    auto bonuses = inventory_.GetTotalBonuses();
    max_hp_ = base_max_hp_ + bonuses.hp_bonus;

    Damage = base_damage_ + bonuses.damage_bonus;
    Hard_Damage = base_hard_damage_ + bonuses.hard_damage_bonus;
    Defense = base_defense_ + bonuses.defense_bonus;
    HP = std::min(HP, max_hp_);
}