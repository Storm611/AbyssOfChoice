#ifndef BATTLE_EVENT_H
#define BATTLE_EVENT_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Enemy.h"

class BattleEvent {
public:
    BattleEvent(Player& player);
    void addEnemy(const Enemy& enemy);
    void start();
    void ShowFinalChoice();
    bool Final();
private:
    void battle(Enemy& enemy);

    Player& player;
    std::vector<Enemy> enemies;
};

#endif // BATTLE_EVENT_H