#ifndef RPG_GAME_GAME_H
#define RPG_GAME_GAME_H

#include "Player.h"
#include "Shop.h"
#include "LevelManager.h"

class Game {
public:
    Game();
    void Play();

private:
    void ShowMainMenu() const;
    void ClearScreen() const;
    void ClearInputBuffer() const;
    void HandleAdventureMode();
    void HandleInventory();
    void HandleShop();
    void HandleStats();
    void HandleSave();
    void HandleLoad();

    Player player_;
    Shop shop_;
    LevelManager level_manager_;
    bool game_running_;
};

#endif 