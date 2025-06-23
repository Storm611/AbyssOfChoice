

#include "level.h"

#include <iostream>

Level::Level(const std::string& id, const std::vector<Enemy>& enemies,
    int reward_xp, int reward_money,
    const std::vector<std::string>& next_levels)
    : id_(id),
    enemies_(enemies),
    reward_xp_(reward_xp),
    reward_money_(reward_money),
    is_completed_(false),
    next_levels_(next_levels) {
}

bool Level::Start(Player& player) {
    std::cout << "\n=== LEVEL " << id_ << " ===\n";
    BattleEvent battle(player);

    for (auto& enemy : enemies_) {
        battle.addEnemy(enemy);
    }

    battle.start();

    if (player.GetHp() > 0) {
        is_completed_ = true;
        player.GainExperience(reward_xp_);
        player.GainMoney(reward_money_);
        player.Heal(player.GetMaxHp());
        std::cout << "Level " << id_ << " completed! Reward: "
            << reward_xp_ << " XP + " << reward_money_ << " gold.\n";
        return true;
    }

    return false;
}

void Level::MarkAsCompleted() {
    is_completed_ = true;
}

bool Level::IsLevelCompleted() const {
    return is_completed_;
}

const std::string& Level::GetId() const {
    return id_;
}

const std::vector<std::string>& Level::GetNextLevels() const {
    return next_levels_;
}