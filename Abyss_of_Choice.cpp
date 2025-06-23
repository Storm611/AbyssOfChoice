

#include <iostream>
#include "XP.h"
#include "Character.h"
#include "player.h"
#include "Enemy.h"
#include "BattleEvent.h"
#include "PlayerInventory.h"
#include "Inventory.h"
#include "LevelManager.h"
#include "Shop.h"



int main() {


    Player player(100, 10, 15, 5, 3);
    // Экипируем предметы
    player.equipItem(PlayerInventory::ItemType::HELMET,"Father_hat",1,0,0,1);
    player.equipItem(PlayerInventory::ItemType::CHEST, "T-shirt", 5, 0, 0,3);
    player.equipItem(PlayerInventory::ItemType::LEGS, "Pants", 5, 0, 0, 3);
    player.equipItem(PlayerInventory::ItemType::WEAPON, "Pitchfork", 0, 4, 4, 0);
    // Показываем инвентарь
    player.showInventory();

    LevelManager levelManager;


    levelManager.selectLevel(player);

    return 0;
}