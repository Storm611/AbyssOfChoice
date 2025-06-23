#ifndef RPG_GAME_LEVEL_MANAGER_H_
#define RPG_GAME_LEVEL_MANAGER_H_

#include <unordered_map>
#include <string>
#include <vector>
#include "level.h"

class Player;

class LevelManager {
public:
	LevelManager();
	~LevelManager();

	void LoadGame();
	void Final_choice();
	void SaveGame();
	bool SelectLevel(Player& player);

private:
	void InitializeLevels();

	std::unordered_map<std::string, Level> levels_;
	std::string save_file_name_ = "savegame.txt";
	std::string current_level_id_ = "1";
};

#endif 