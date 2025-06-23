#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "Character.h"

class Enemy : public Character {
public:
    Enemy(int hp, int damage, int hard_damage, int defense, int experienceReward, int moneyReward);

    void takeDamage(int damage);

    int GetExperienceReward() const;
    int GetMoneyReward() const;

private:
    void die();

    int experienceReward;
    int moneyReward;
};

#endif