#ifndef FINAL_CREDITS_EVENT_H
#define FINAL_CREDITS_EVENT_H

#include "Player.h"

class FinalCreditsEvent {
public:
    FinalCreditsEvent(Player& player) : player(player) {}
    void Start();

private:
    Player& player;
    void ShowCredits();
    void ShowEndingChoice();
    void GoodEnding();
    void EvilEnding();
};

#endif 