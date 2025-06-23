#pragma once
#include "Character.h"
#include "XP.h"
#include "PlayerInventory.h"
#include <algorithm>
#include <iostream>
#include "Shop.h"
class Player : public Character {
public:
    Player(int hp, int damage, int hard_damage, int defense, int health_potion)
        : Character(hp, damage, hard_damage, defense),
        level(1), base_max_hp(hp), base_damage(damage),
        base_hard_damage(hard_damage), base_defense(defense),
        money(0), health_potion(health_potion) {
        recalculateStats();
    }

    // —истема уровней
    void gainExperience(int exp) {
        xp.addExperience(exp);
        while (xp.checkLevelUp()) {
            xp.levelUp();
            levelUp();
        }
    }

    int getLevel() const { return level; }

    // ”правление здоровьем
    int getMaxHp() const { return max_hp; }

    void heal(int amount) {
        HP += amount;
        if (HP > max_hp) {
            HP = max_hp;
        }
    }

    bool useHealthPotion() {
        if (health_potion > 0) {
            int heal_amount = (getMaxHp() * 40) / 100;
            heal(heal_amount);
            health_potion--;
            std::cout << "Used health potion. HP: " << HP << "/" << max_hp << "\n";
            return true;
        }
        std::cout << "No health potions left!\n";
        return false;
    }

    // Ёкономика
    void gainMoney(int amount) {
        money += amount;
        std::cout << "Obtained " << amount << " gold. Total: " << money << "\n";
    }

    int getMoney() const { return money; }

    // »нвентарь
    void equipItem(PlayerInventory::ItemType slot, const std::string& name,
        int hp_bonus, int damage_bonus,
        int hard_damage_bonus, int defense_bonus) {
        unequipItem(slot);
        PlayerInventory::ItemStats newItem(name, hp_bonus, damage_bonus,
            hard_damage_bonus, defense_bonus);
        inventory.equipItem(slot, newItem);
        applyItemBonuses(newItem, true);
        std::cout << "Equipped " << name << " (" << PlayerInventory::slotToString(slot) << ")\n";
        heal(getMaxHp());
    }

    void unequipItem(PlayerInventory::ItemType slot) {
        const auto& item = inventory.getItem(slot);
        if (item.name != "None") {
            applyItemBonuses(item, false);
            inventory.unequipItem(slot);
            std::cout << "Unequipped " << item.name << "\n";
        }
    }

    void showInventory() const {
        std::cout << "\n=== INVENTORY ===\n";
        std::cout << "Gold: " << money << "\n";
        std::cout << "Health potions: " << health_potion << "\n\n";
        inventory.showInventory();

        auto bonuses = inventory.getTotalBonuses();
        std::cout << "\nTotal bonuses:\n";
        std::cout << "HP: +" << bonuses.hp_bonus << "\n";
        std::cout << "Damage: +" << bonuses.damage_bonus << "\n";
        std::cout << "Heavy Damage: +" << bonuses.hard_damage_bonus << "\n";
        std::cout << "Defense: +" << bonuses.defense_bonus << "\n";
    }

    void showStats() const {
        std::cout << "\n=== PLAYER STATS ===\n";
        std::cout << "Level: " << level << "\n";
        std::cout << "HP: " << HP << "/" << max_hp << "\n";
        std::cout << "Damage: " << Damage << " (+" << Damage - base_damage << ")\n";
        std::cout << "Heavy Damage: " << Hard_Damage << " (+" << Hard_Damage - base_hard_damage << ")\n";
        std::cout << "Defense: " << Defense << " (+" << Defense - base_defense << ")\n";
    }





private:
    PlayerInventory inventory;
    XP xp;
    int level;
    int max_hp;
    int base_max_hp;
    int base_damage;
    int base_hard_damage;
    int base_defense;
    int money;
    int health_potion;

    void levelUp() {
        level++;
        base_max_hp += 10 + level;
        base_damage += 2 + level / 2;
        base_hard_damage += 3 + level / 2;
        base_defense += 1 + level / 3;

        recalculateStats();
        HP = max_hp;

        std::cout << "\nLEVEL UP! (" << level << ")\n";
        std::cout << "HP: " << max_hp << " (+" << 10 + level << ")\n";
        std::cout << "Damage: " << Damage << " (+" << 2 + level / 2 << ")\n";
        std::cout << "Heavy Damage: " << Hard_Damage << " (+" << 3 + level / 2 << ")\n";
        std::cout << "Defense: " << Defense << " (+" << 1 + level / 3 << ")\n";
    }

    void applyItemBonuses(const PlayerInventory::ItemStats& item, bool equip) {
        int modifier = 0.5;
        base_max_hp += modifier * item.hp_bonus;
        base_damage += modifier * item.damage_bonus;
        base_hard_damage += modifier * item.hard_damage_bonus;
        base_defense += modifier * item.defense_bonus;
        recalculateStats();
    }

    void recalculateStats() {
        auto bonuses = inventory.getTotalBonuses();
        max_hp = base_max_hp + bonuses.hp_bonus;
        Damage = base_damage + bonuses.damage_bonus;
        Hard_Damage = base_hard_damage + bonuses.hard_damage_bonus;
        Defense = base_defense + bonuses.defense_bonus;
        HP = std::min(HP, max_hp);
    }
};