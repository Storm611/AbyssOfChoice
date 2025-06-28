#ifndef XP_H
#define XP_H

#include <fstream>
#include <string>

class XP {
public:
    XP();

    void addExperience(int exp);
    bool checkLevelUp() const;
    void levelUp();

    int getLevel() const;
    int getExperience() const;
    int getNextLevelXP() const;

    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);

private:
    int experience;
    int level;

    static constexpr int BASE_XP_PER_LEVEL = 100;
    static constexpr int HIGH_LEVEL_XP_BONUS = 7;
    static constexpr int HIGH_LEVEL_THRESHOLD = 10;
    static const std::string SAVE_FILE_HEADER;

    int calculateLevelXPRequirement() const;
};

#endif