#ifndef XP_H_
#define XP_H_

#include <fstream>
#include <string>

class XP {
public:
	XP();

	void addExperience(int exp);
	bool checkLevelUp();
	void levelUp();
	int getLevel() const;

	void saveToFile(std::ofstream& file) const;
	void loadFromFile(std::ifstream& file);

private:
	int experience;
	int level;
};

#endif