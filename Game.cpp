#include "Game.h"
#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else

#endif

Game::Game() :
    player_(100, 10, 15, 5, 3),
    game_running_(true) {
    player_.EquipItem(PlayerInventory::ItemType::HELMET, "Father's Hat", 5, 0, 0, 1);
    player_.EquipItem(PlayerInventory::ItemType::CHEST, "T-shirt", 5, 0, 0, 0);
    player_.EquipItem(PlayerInventory::ItemType::LEGS, "Pants", 5, 0, 0, 0);
    player_.EquipItem(PlayerInventory::ItemType::WEAPON, "Pitchfork", 0, 4, 4, 0);
}

void Game::Play() {
    while (game_running_ && player_.GetHP() > 0) {
        ShowMainMenu();

        int choice;
        std::cin >> choice;
        ClearInputBuffer();
        ClearScreen();

        switch (choice) {
        case 1: HandleAdventureMode(); break;
        case 2: HandleInventory(); break;
        case 3: HandleShop(); break;
        case 4: HandleStats(); break;
        case 5: HandleSave(); break;
        case 6: HandleLoad(); break;
        case 0:
            player_.SaveGame();
            level_manager_.SaveGame();
            game_running_ = false;
            break;
        default:
            std::cout << "Invalid choice!\n";
            std::cout << "\nPress Enter to continue...";
            ClearInputBuffer();
            ClearScreen();
            break;
        }
    }

    if (player_.GetHP() > 0) {
        std::cout << "\nThanks for playing! Goodbye!\n";
    }
}

void Game::ShowMainMenu() const {
    std::cout << "\n=== MAIN MENU ===\n";
    std::cout << "1. Adventure Mode\n";
    std::cout << "2. Inventory\n";
    std::cout << "3. Shop\n";
    std::cout << "4. Stats\n";
    std::cout << "5. Save Game\n";
    std::cout << "6. Load Game\n";
    std::cout << "0. Exit\n";
    std::cout << "Your choice: ";
}

void Game::ClearScreen() const {
    system(CLEAR_SCREEN);
}

void Game::ClearInputBuffer() const {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::HandleAdventureMode() {
    bool level_completed = level_manager_.SelectLevel(player_);
    if (player_.GetHP() <= 0) {
        std::cout << "\nGAME OVER! You died.\n";
        game_running_ = false;
    }
    ClearScreen();
}

void Game::HandleInventory() {
    player_.ShowInventory();
    std::cout << "\nPress Enter to continue...";
    ClearInputBuffer();
    ClearScreen();
}

void Game::HandleShop() {
    bool shopping = true;
    while (shopping) {
        ClearScreen();
        std::cout << "\n=== SHOP ===\n";
        std::cout << "Your gold: " << player_.GetMoney() << "\n\n";

        const auto& items = shop_.GetAvailableItems();
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i].name
                << " | HP: +" << items[i].hp_bonus
                << " | Dmg: +" << items[i].damage_bonus
                << " | Def: +" << items[i].defense_bonus
                << " | Price: " << shop_.GetItemPrice(i) << " gold\n";
        }
        std::cout << "0. Exit shop\n";
        std::cout << "Your choice: ";

        int item_choice;
        std::cin >> item_choice;
        ClearInputBuffer();

        if (item_choice == 0) {
            shopping = false;
        }
        else if (item_choice > 0 && item_choice <= static_cast<int>(items.size())) {
            ClearScreen();
            const auto& item = items[item_choice - 1];
            int price = shop_.GetItemPrice(item_choice - 1);

            if (player_.GetMoney() >= price) {
                player_.GainMoney(-price);

                if (item.name == "Health Potion") {
                    player_.AddHealthPotion(1);
                    std::cout << "Bought 1 Health Potion!\n";
                }
                else {
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

                    player_.EquipItem(slot, item.name, item.hp_bonus,
                        item.damage_bonus, 0, item.defense_bonus);
                    std::cout << "Equipped " << item.name << "!\n";
                }
            }
            else {
                std::cout << "Not enough gold!\n";
            }
            std::cout << "\nPress Enter to continue...";
            ClearInputBuffer();
        }
        else {
            std::cout << "Invalid choice!\n";
            std::cout << "\nPress Enter to continue...";
            ClearInputBuffer();
        }
    }
    ClearScreen();
}

void Game::HandleStats() {
    player_.ShowStats();
    std::cout << "\nPress Enter to continue...";
    ClearInputBuffer();
    ClearScreen();
}

void Game::HandleSave() {
    player_.SaveGame();
    level_manager_.SaveGame();
    std::cout << "Game saved!\n";
    std::cout << "\nPress Enter to continue...";
    ClearInputBuffer();
    ClearScreen();
}

void Game::HandleLoad() {
    player_.LoadGame();
    level_manager_.LoadGame();
    std::cout << "Game loaded!\n";
    std::cout << "\nPress Enter to continue...";
    ClearInputBuffer();
    ClearScreen();
}