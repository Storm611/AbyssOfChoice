

#include "levelmanager.h"
#include "player.h"
#include "FinalCreditsEvent.h"
#include <fstream>
#include <iostream>
#include <sstream>

LevelManager::LevelManager() {
    InitializeLevels();
    LoadGame();
}

LevelManager::~LevelManager() {
    SaveGame();
}

void LevelManager::LoadGame() {
    std::ifstream save_file(save_file_name_);
    if (!save_file) {
        std::cout << "No save file found. Starting new game.\n";
        return;
    }

    std::string line;
    while (std::getline(save_file, line)) {
        if (line == "CURRENT_LEVEL") {
            if (std::getline(save_file, current_level_id_)) {
                continue;
            }
        }

        auto it = levels_.find(line);
        if (it != levels_.end()) {
            it->second.MarkAsCompleted();
        }
    }
    save_file.close();
    std::cout << "Game loaded successfully! Current level: "
        << current_level_id_ << "\n";
}


void LevelManager::SaveGame() {
    std::ofstream save_file(save_file_name_);
    if (!save_file) {
        std::cerr << "Error saving game!\n";
        return;
    }

    save_file << "CURRENT_LEVEL\n";
    save_file << current_level_id_ << "\n";

    for (const auto& pair : levels_) {
        if (pair.second.IsLevelCompleted()) {
            save_file << pair.first << "\n";
        }
    }
    save_file.close();
}

bool LevelManager::SelectLevel(Player& player) {
    while (true) {
        std::cout << "\n=== LEVEL SELECT ===\n";
        std::cout << "Current progress: " << current_level_id_ << "\n";
        std::cout << "Player HP: " << player.GetHp() << "/"
            << player.GetMaxHp() << "\n";

        Level& current_level = levels_.at(current_level_id_);
        const auto& next_levels = current_level.GetNextLevels();

        if (next_levels.empty() && current_level_id_ == "5.2") {
            FinalCreditsEvent credits(player);
            credits.Start();

            std::cout << "You've completed all available levels!\n";
            return false;
        }

        std::cout << "Available levels:\n";
        for (size_t i = 0; i < next_levels.size(); ++i) {
            std::cout << i + 1 << ". " << next_levels[i];
            if (levels_.at(next_levels[i]).IsLevelCompleted()) {
                std::cout << " [COMPLETED]";
            }
            std::cout << "\n";
        }

        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) return false;

        if (choice < 1 || choice > static_cast<int>(next_levels.size())) {
            std::cout << "Invalid choice!\n";
            continue;
        }

        std::string selected_level_id = next_levels[choice - 1];
        Level& selected_level = levels_.at(selected_level_id);

        if (selected_level.Start(player)) {
            current_level_id_ = selected_level_id;
        }

        if (player.GetHp() <= 0) {
            return false;
        }
    }
}

void LevelManager::InitializeLevels() {
    // Константы для сообщений
    const std::string BASIC_MSG = "Enemy defeated! Gained ";
    const std::string MINIBOSS_MSG = "Mini-boss slain! Awarded ";
    const std::string BOSS_MSG = "BOSS DEFEATED! Obtained ";
    
    // Уровень 1 (стартовый)
    levels_.emplace("1", Level("1", {
        Enemy(30, 5, 8, 2, 20, 10, BASIC_MSG)
    }, 50, 300, {"1.1", "1.2", "1.3"}));

    // Под-уровни 1.X
    levels_.emplace("1.1", Level("1.1", {
        Enemy(40, 15, 10, 3, 25, 15, BASIC_MSG)
    }, 60, 400, {"2.1", "2.2"}));

    levels_.emplace("1.2", Level("1.2", {
        Enemy(50, 15, 12, 4, 30, 20, BASIC_MSG)
    }, 70, 500, {"2.1", "2.2", "2.3"}));

    levels_.emplace("1.3", Level("1.3", {
        Enemy(60, 20, 15, 5, 35, 25, MINIBOSS_MSG)
    }, 40, 500, {"2.2", "2.3"}));

    // Уровни 2.X
    levels_.emplace("2.1", Level("2.1", {
        Enemy(70, 20, 30, 6, 40, 30, BASIC_MSG),
        Enemy(75, 15, 50, 5, 35, 25, MINIBOSS_MSG)
    }, 90, 700, {"3.1", "3.2"}));

    levels_.emplace("2.2", Level("2.2", {
        Enemy(80, 25, 25, 7, 45, 35, BASIC_MSG),
        Enemy(85, 25, 20, 6, 40, 30, MINIBOSS_MSG)
    }, 100, 800, {"3.1", "3.2", "3.3"}));

    levels_.emplace("2.3", Level("2.3", {
        Enemy(90, 18, 25, 8, 50, 40, BASIC_MSG),
        Enemy(95, 15, 22, 7, 45, 35, MINIBOSS_MSG)
    }, 110, 900, {"3.2", "3.3"}));

    // Уровни 3.X (продвинутые)
    levels_.emplace("3.1", Level("3.1", {
        Enemy(150, 35, 30, 10, 60, 50, BASIC_MSG),
        Enemy(110, 20, 45, 9, 55, 45, MINIBOSS_MSG),
        Enemy(180, 40, 40, 11, 65, 55, MINIBOSS_MSG)
    }, 120, 1000, {"4.2"}));

    levels_.emplace("3.2", Level("3.2", {
        Enemy(140, 30, 35, 12, 70, 60, BASIC_MSG),
        Enemy(120, 25, 40, 11, 65, 55, MINIBOSS_MSG),
        Enemy(150, 35, 40, 13, 75, 65, MINIBOSS_MSG)
    }, 130, 1100, {"4.2"}));

    levels_.emplace("3.3", Level("3.3", {
        Enemy(150, 30, 40, 15, 80, 70, BASIC_MSG),
        Enemy(160, 28, 38, 14, 75, 65, MINIBOSS_MSG),
        Enemy(170, 35, 45, 16, 85, 75, MINIBOSS_MSG)
    }, 150, 1300, {"4.2"}));

    // Уровень 4.2 (пред-финальный)
    levels_.emplace("4.2", Level("4.2", {
        Enemy(100, 25, 30, 10, 50, 40, BASIC_MSG),
        Enemy(110, 28, 32, 11, 55, 45, BASIC_MSG),
        Enemy(120, 30, 35, 12, 60, 50, BASIC_MSG),
        Enemy(130, 32, 38, 13, 65, 55, MINIBOSS_MSG),
        Enemy(140, 35, 40, 14, 70, 60, MINIBOSS_MSG)
    }, 200, 1500, {"5.2"}));

    // Уровень 5.2 (финальный босс)
    levels_.emplace("5.2", Level("5.2", {
        Enemy(500, 50, 70, 30, 200, 500, BOSS_MSG)
    }, 300, 3000, {}));
}