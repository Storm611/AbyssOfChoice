
#ifndef RPG_GAME_LEVEL_H_
#define RPG_GAME_LEVEL_H_

#include <string>
#include <vector>
#include "enemy.h"
#include "player.h"
#include "battleevent.h"

class Level {
public:
    Level(const std::string& id, const std::vector<Enemy>& enemies,
        int reward_xp, int reward_money,
        const std::vector<std::string>& next_levels);


    bool Start(Player& player);

    void MarkAsCompleted();
    bool IsLevelCompleted() const;
    const std::string& GetId() const;
    const std::vector<std::string>& GetNextLevels() const;

private:
    std::string id_;
    std::vector<Enemy> enemies_;
    int reward_xp_;
    int reward_money_;
    bool is_completed_;
    std::vector<std::string> next_levels_;  
};

#endif 