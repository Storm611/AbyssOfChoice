#pragma once
#include "iostream"
#include "Character.h"

class Enemy : public Character {
public:
    Enemy(int hp, int damage, int hard_damage, int defense, int experienceReward, int moneyReward)
        : Character(hp, damage, hard_damage, defense), experienceReward(experienceReward),moneyReward(moneyReward) {}

    void takeDamage(int damage) {
        Character::takeDamage(damage);
        if (getHP() <= 0) {
            die();
        }
    }

    int getExperienceReward() const {
        return experienceReward;
    }
    int getMoneyReward() const {
        return moneyReward;
    }


private:
    void die() {
        std::cout << "Enemy defeated! Rewarding " << experienceReward << " experience points." << std::endl;
        // ����� ����� �������� ������ ��� �������� ����� ������
    }

    int experienceReward; // ���������� �����, ������� ���� ����
    int moneyReward;
};
