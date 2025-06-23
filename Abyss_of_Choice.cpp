#include <iostream>
#include <limits> // Для clearInputBuffer()
#include "Shop.h"
#include "Player.h"
#include "levelManager.h"

void showMainMenu() {
    std::cout << "\n=== MAIN MENU ===\n";
    std::cout << "1. Adventure (Levels)\n";
    std::cout << "2. Inventory\n";
    std::cout << "3. Shop\n";
    std::cout << "4. Character Stats\n";
    std::cout << "5. Save Game\n";
    std::cout << "6. Load Game\n";
    std::cout << "0. Exit\n";
    std::cout << "Your choice: ";
}


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Инициализация игровых объектов
    Player player(100, 10, 15, 5, 3);
    player.EquipItem(PlayerInventory::ItemType::HELMET, "Father's Hat", 5, 0, 0, 3);
    player.EquipItem(PlayerInventory::ItemType::CHEST, "T-shirt", 5, 0, 0, 3);
    player.EquipItem(PlayerInventory::ItemType::LEGS, "Pants", 5, 0, 0, 3);
    player.EquipItem(PlayerInventory::ItemType::WEAPON, "Pitchfork", 0, 4, 4, 0);

    Shop shop;
    LevelManager levelManager;

    bool gameRunning = true;
    while (gameRunning && player.getHP() > 0) {
        showMainMenu();

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: { // Режим приключений
            bool levelCompleted = levelManager.selectLevel(player);
            if (player.getHP() <= 0) {
                std::cout << "\nGAME OVER! You died.\n";
                gameRunning = false;
            }
            break;
        }
        case 2: // Инвентарь
            player.ShowInventory();
            break;
        case 3: { // Магазин
            bool shopping = true;
            while (shopping) {
                // Показываем ассортимент магазина
                std::cout << "\n=== SHOP ===\n";
                std::cout << "Your gold: " << player.GetMoney() << "\n\n";

                const auto& items = shop.getAvailableItems();
                for (size_t i = 0; i < items.size(); ++i) {
                    std::cout << i + 1 << ". " << items[i].name
                        << " | HP: +" << items[i].hp_bonus
                        << " | Dmg: +" << items[i].damage_bonus
                        << " | Def: +" << items[i].defense_bonus
                        << " | Price: " << shop.getItemPrice(i) << " gold\n";
                }
                std::cout << "0. Exit shop\n";
                std::cout << "Your choice: ";

                int itemChoice;
                std::cin >> itemChoice;
                clearInputBuffer();

                if (itemChoice == 0) {
                    shopping = false;
                }
                else if (itemChoice > 0 && itemChoice <= static_cast<int>(items.size())) {
                    const auto& item = items[itemChoice - 1];
                    int price = shop.getItemPrice(itemChoice - 1);

                    if (player.GetMoney() >= price) {
                        player.GainMoney(-price);

                        if (item.name == "Health Potion") {
                            player.AddHealthPotion(1);
                            std::cout << "Bought 1 Health Potion!\n";
                        }
                        else {
                            // Определяем тип слота
                            PlayerInventory::ItemType slot;
                            if (item.name.find("Helmet") != std::string::npos) {
                                slot = PlayerInventory::ItemType::HELMET;
                            }
                            else if (item.name.find("Armor") != std::string::npos ||
                                item.name.find("Mail") != std::string::npos) {
                                slot = PlayerInventory::ItemType::CHEST;
                            }
                            else if (item.name.find("Pants") != std::string::npos ||
                                item.name.find("Greaves") != std::string::npos) {
                                slot = PlayerInventory::ItemType::LEGS;
                            }
                            else {
                                slot = PlayerInventory::ItemType::WEAPON;
                            }

                            player.EquipItem(slot, item.name, item.hp_bonus,
                                item.damage_bonus, 0, item.defense_bonus);
                            std::cout << "Equipped " << item.name << "!\n";
                        }
                    }
                    else {
                        std::cout << "Not enough gold!\n";
                    }
                }
                else {
                    std::cout << "Invalid choice!\n";
                }
            }
            break;
        }
        case 4: // Статистика
            player.ShowStats();
            break;
        case 5: // Сохранение
            player.SaveGame();  // Сохраняем данные игрока, инвентаря и XP
            levelManager.saveGame();
            std::cout << "Game saved!\n";
            break;
        case 6: // Загрузка
            player.LoadGame();  // Загружаем данные игрока, инвентаря и XP
            levelManager.loadGame();
            std::cout << "Game loaded!\n";
            break;
        case 0: // Выход
            player.SaveGame();  // Сохраняем данные игрока, инвентаря и XP
            levelManager.saveGame();
            gameRunning = false;
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }

    if (player.getHP() > 0) {
        std::cout << "\nThanks for playing! Goodbye!\n";
    }

    return 0;
}