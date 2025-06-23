
#ifndef RPG_GAME_PLAYER_INVENTORY_H_
#define RPG_GAME_PLAYER_INVENTORY_H_

#include <map>
#include <string>

class PlayerInventory {
public:
    enum class ItemType { HELMET, CHEST, LEGS, WEAPON };

    struct ItemStats {
        std::string name;
        int hp_bonus;
        int damage_bonus;
        int hard_damage_bonus;
        int defense_bonus;

        ItemStats(const std::string& n = "None", int hp = 0, int dmg = 0,
            int hard_dmg = 0, int def = 0);

        void SaveToStream(std::ostream& os) const;
        void LoadFromStream(std::istream& is);
    };

    PlayerInventory();

    void EquipItem(ItemType slot, const ItemStats& item);
    void UnequipItem(ItemType slot);
    const ItemStats& GetItem(ItemType slot) const;
    void ShowInventory() const;
    static std::string SlotToString(ItemType slot);
    ItemStats GetTotalBonuses() const;

    void SaveToFile(std::ofstream& file) const;
    void LoadFromFile(std::ifstream& file);

private:
    std::map<ItemType, ItemStats> equipped_items_;
};

#endif  // RPG_GAME_PLAYER_INVENTORY_H_