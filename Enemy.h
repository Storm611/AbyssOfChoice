#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <string>

class Enemy : public Character {
public:

    Enemy(int hp, int damage, int hard_damage, int defense,
        int experienceReward, int moneyReward,
        const std::string& deathMessage);

    void takeDamage(int damage);


    int GetExperienceReward() const;
    int GetMoneyReward() const;

private:
    void die();  

    int experienceReward;  
    int moneyReward;      
    std::string deathMessage;  
};

#endif