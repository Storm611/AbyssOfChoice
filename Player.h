

#ifndef RPG_GAME_PLAYER_H_
#define RPG_GAME_PLAYER_H_

#include <string>
#include "character.h"
#include "XP.h"
#include "PlayerInventory.h"

class Player : public Character {
public:
    Player(int hp, int damage, int hard_damage, int defense, int health_potion);

    void GainExperience(int exp);
    int GetLevel() const;
    int GetMaxHp() const;
    int GetHp() const;
    int GetBaseMaxHp() const;
    void Heal(int amount);
    bool UseHealthPotion();

    // Economy
    void GainMoney(int amount);
    int GetMoney() const;

    // Inventory
    void EquipItem(PlayerInventory::ItemType slot, const std::string& name,
        int hp_bonus, int damage_bonus,
        int hard_damage_bonus, int defense_bonus);
    void UnequipItem(PlayerInventory::ItemType slot);
    void ShowInventory() const;
    void ShowStats() const;
    void AddHealthPotion(int count);
    void BuyItem(const PlayerInventory::ItemStats& item, int price);

    void SaveGame();
    void LoadGame();

private:
    void LevelUp();
    void ApplyItemBonuses(const PlayerInventory::ItemStats& item, bool equip);
    void RecalculateStats();

    PlayerInventory inventory_;
    XP xp_;
    int level_;
    int max_hp_;
    int base_max_hp_;
    int base_damage_;
    int base_hard_damage_;
    int base_defense_;
    int money_;
    int health_potion_;
};

#endif  // RPG_GAME_PLAYER_H_