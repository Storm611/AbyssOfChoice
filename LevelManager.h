#pragma once
#include <unordered_map>
#include <vector>
#include "Level.h"
#include <fstream>
#include <sstream>

class LevelManager {
public:
    LevelManager() {
        initializeLevels();
        loadGame();
    }
    ~LevelManager() {
        saveGame();  // Сохраняем при завершении
    }

    void loadGame() {
        std::ifstream saveFile(saveFileName);
        if (!saveFile) {
            std::cout << "No save file found. Starting new game.\n";
            return;
        }

        std::string line;
        while (std::getline(saveFile, line)) {
            if (line == "CURRENT_LEVEL") {
                // Следующая строка содержит текущий уровень
                if (std::getline(saveFile, currentLevelId)) {
                    continue;
                }
            }

            auto it = levels.find(line);
            if (it != levels.end()) {
                it->second.MarkAsCompleted();
            }
        }
        saveFile.close();
        std::cout << "Game loaded successfully! Current level: " << currentLevelId << "\n";
    }

    void saveGame() {
        std::ofstream saveFile(saveFileName);
        if (!saveFile) {
            std::cerr << "Error saving game!\n";
            return;
        }

        // Сохраняем текущий уровень
        saveFile << "CURRENT_LEVEL\n";
        saveFile << currentLevelId << "\n";

        // Сохраняем пройденные уровни
        for (const auto& pair : levels) {
            if (pair.second.IsLevelCompleted()) {
                saveFile << pair.first << "\n";
            }
        }
        saveFile.close();
    }
    // Показывает доступные уровни и позволяет выбрать
    bool selectLevel(Player& player) {
        while (true) {
            std::cout << "\n=== LEVEL SELECT ===\n";
            std::cout << "Current progress: " << currentLevelId << "\n";
            std::cout << "Player HP: " << player.getHP() << "/" << player.GetMaxHp() << "\n";

            // Получаем текущий уровень
            Level& currentLevel = levels.at(currentLevelId);
            const auto& nextLevels = currentLevel.GetNextLevels();

            if (nextLevels.empty()) {
                std::cout << "You've completed all available levels!\n";
                return false;
            }

            std::cout << "Available levels:\n";
            for (size_t i = 0; i < nextLevels.size(); ++i) {
                std::cout << i + 1 << ". " << nextLevels[i];
                if (levels.at(nextLevels[i]).IsLevelCompleted()) {
                    std::cout << " [COMPLETED]";
                }
                std::cout << "\n";
            }

            std::cout << "0. Exit\n";
            std::cout << "Your choice: ";

            int choice;
            std::cin >> choice;

            if (choice == 0) return false;

            if (choice < 1 || choice > static_cast<int>(nextLevels.size())) {
                std::cout << "Invalid choice!\n";
                continue;
            }

            std::string selectedLevelId = nextLevels[choice - 1];
            Level& selectedLevel = levels.at(selectedLevelId);

            if (selectedLevel.Start(player)) {
                // Успешно завершили уровень - обновляем текущий
                currentLevelId = selectedLevelId;
            }

            if (player.getHP() <= 0) {
                return false;
            }
        }
    }

private:
    std::unordered_map<std::string, Level> levels;
    std::string saveFileName = "savegame.txt";
    std::string currentLevelId = "1";
    void initializeLevels() {
        // Уровень 1 (начальный)
        levels.emplace("1", Level("1", { Enemy(30, 5, 8, 2, 20, 10) }, 50, 300, { "1.1", "1.2", "1.3" }));

        // Уровни 1.X
        levels.emplace("1.1", Level("1.1", { Enemy(40, 7, 10, 3, 25, 15) }, 60, 400, { "2.1", "2.2" }));
        levels.emplace("1.2", Level("1.2", { Enemy(50, 8, 12, 4, 30, 20) }, 70, 500, { "2.1", "2.2", "2.3" }));
        levels.emplace("1.3", Level("1.3", { Enemy(60, 10, 15, 5, 35, 25) }, 80, 600, { "2.2", "2.3" }));

        levels.emplace("2.1", Level("2.1", {
            Enemy(70, 20, 30, 6, 40, 30),
            Enemy(75, 15, 50, 5, 35, 25)
            }, 90, 700, { "3.1", "3.2" }));

        levels.emplace("2.2", Level("2.2", {
            Enemy(80, 25, 25, 7, 45, 35),
            Enemy(85, 25, 20, 6, 40, 30)
            }, 100, 800, { "3.1", "3.2", "3.3" }));

        levels.emplace("2.3", Level("2.3", {
            Enemy(90, 18, 25, 8, 50, 40),
            Enemy(95, 15, 22, 7, 45, 35)
            }, 110, 900, { "3.2", "3.3" }));

        // Уровни 3.X (финальные, по 3 врага)
        levels.emplace("3.1", Level("3.1", {
            Enemy(150, 35, 30, 10, 60, 50),
            Enemy(110, 20, 45, 9, 55, 45),
            Enemy(180, 40, 40, 11, 65, 55)
            }, 120, 1000, {}));

        levels.emplace("3.2", Level("3.2", {
            Enemy(140, 30, 35, 12, 70, 60),
            Enemy(120, 25, 40, 11, 65, 55),
            Enemy(150, 35, 40, 13, 75, 65)
            }, 130, 1100, {}));

        levels.emplace("3.3", Level("3.3", {
            Enemy(150, 30, 40, 15, 80, 70),
            Enemy(160, 28, 38, 14, 75, 65),
            Enemy(170, 35, 45, 16, 85, 75)
            }, 150, 1300, {}));
    }






};