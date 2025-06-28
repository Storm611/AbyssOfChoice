#include "Enemy.h"
#include <string>

Enemy::Enemy(int hp, int damage, int hard_damage, int defense,
    int experienceReward, int moneyReward, const std::string& deathMessage)
    : Character(hp, damage, hard_damage, defense),
    experienceReward(experienceReward),
    moneyReward(moneyReward),
    deathMessage(deathMessage) {
}

void Enemy::takeDamage(int damage) {
    Character::TakeDamage(damage);
    if (GetHP() <= 0) {
        die();
    }
}

int Enemy::GetExperienceReward() const {
    return experienceReward;
}

int Enemy::GetMoneyReward() const {
    return moneyReward;
}

void Enemy::die() {
    std::cout << deathMessage << experienceReward << " experience points." << std::endl;
}