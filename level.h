#pragma once
#include <vector>
#include <string>
#include "Enemy.h"
#include "Player.h"
#include "BattleEvent.h"    
class Level {
public:
    Level(const std::string& id, const std::vector<Enemy>& enemies, int rewardXP, int rewardMoney, const std::vector<std::string>& nextLevels)
        : id(id), enemies(enemies), rewardXP(rewardXP), rewardMoney(rewardMoney), nextLevels(nextLevels), isCompleted(false) {
    }

    // «апуск уровн€ (возвращает true, если игрок победил)
    bool start(Player& player) {
        std::cout << "\n=== LEVEL " << id << " ===\n";
        BattleEvent battle(player);

        for (auto& enemy : enemies) {
            battle.addEnemy(enemy);
        }

        battle.start();

        if (player.getHP() > 0) {
            isCompleted = true;
            player.gainExperience(rewardXP);
            player.gainMoney(rewardMoney);
            player.heal(player.getMaxHp());
            std::cout << "Level " << id << " completed! Reward: "
                << rewardXP << " XP + " << rewardMoney << " gold.\n";
            return true;
        }

        return false;
    }

    void markAsCompleted() {
        isCompleted = true;
    }

    bool isLevelCompleted() const { return isCompleted; }
    const std::string& getId() const { return id; }
    const std::vector<std::string>& getNextLevels() const { return nextLevels; }

private:
    std::string id;
    std::vector<Enemy> enemies;
    int rewardXP;
    int rewardMoney;
    bool isCompleted;
    std::vector<std::string> nextLevels; //  акие уровни открываютс€ после этого
};