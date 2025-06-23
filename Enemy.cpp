#include "Enemy.h"

Enemy::Enemy(int hp, int damage, int hard_damage, int defense, int experienceReward, int moneyReward)
    : Character(hp, damage, hard_damage, defense), experienceReward(experienceReward), moneyReward(moneyReward) {
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
    std::cout << "Enemy defeated! Rewarding " << experienceReward << " experience points." << std::endl;
}