#pragma once
#include "Character.h"
#include "XP.h"
#include "PlayerInventory.h"
#include <algorithm>
#include <iostream>

class Player : public Character {
public:
    Player(int hp, int damage, int hard_damage, int defense,int health_potion)
        : Character(hp, damage, hard_damage, defense),
        level(1), max_hp(hp), money(0) {}

    // —истема опыта и уровней
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
            int heal_amount = (getMaxHp() * 40) / 100; // 40% от максимального HP
            heal(heal_amount);
            health_potion--;
            return true;
        }
        return false;
    }



    // Ёкономика
    void gainMoney(int amount) {
        money += amount;
        std::cout << "Player gained " << amount << " money. Total money: " << money << std::endl;
    }

    int getMoney() const { return money; }

    // ”лучшение характеристик
    void improveArmor(int amount) {
        Defense += amount;
    }

    // —истема инвентар€
    void equipItem(Inventory::ItemType slot, const std::string& name,
        int hp_bonus, int damage_bonus,
        int hard_damage_bonus, int defense_bonus) {
        unequipItem(slot);

        Inventory::ItemStats newItem(name, hp_bonus, damage_bonus,
            hard_damage_bonus, defense_bonus);
        inventory.equipItem(slot, newItem);
        applyItemBonuses(newItem, true);

        std::cout << "Equipped " << name << " (" << Inventory::slotToString(slot)
            << ")" << std::endl;
    }

    void unequipItem(Inventory::ItemType slot) {
        const auto& item = inventory.getItem(slot);
        if (item.name != "None") {
            applyItemBonuses(item, false);
            inventory.unequipItem(slot);
            std::cout << "Unequipped " << item.name << std::endl;
        }
    }

    void showInventory() const {
        inventory.showInventory();
    }

private:
    void levelUp() {
        level++;
        max_hp += level;
        HP += level;
        Damage += level;
        Hard_Damage += level;

        std::cout << "Level up! Now you are level " << level
            << ". HP: " << max_hp << ", Damage: " << Damage
            << ", Hard Damage: " << Hard_Damage << std::endl;
    }

    void applyItemBonuses(const Inventory::ItemStats& item, bool equip) {
        int modifier = equip ? 1 : -1;

        max_hp += modifier * item.hp_bonus;
        HP = std::min(HP, max_hp);
        Damage += modifier * item.damage_bonus;
        Hard_Damage += modifier * item.hard_damage_bonus;
        Defense += modifier * item.defense_bonus;
    }

    Inventory inventory;
    int level;
    int max_hp;
    XP xp;
    int money;
    int health_potion;
};