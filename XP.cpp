#include "XP.h"

const std::string XP::SAVE_FILE_HEADER = "XP";

XP::XP() : experience(0), level(1) {}

void XP::addExperience(int exp) {
    if (exp > 0) {
        experience += exp;
    }
}

bool XP::checkLevelUp() const {
    return experience >= calculateLevelXPRequirement();
}

void XP::levelUp() {
    experience -= calculateLevelXPRequirement();
    level++;
}

int XP::getLevel() const {
    return level;
}

int XP::getExperience() const {
    return experience;
}

int XP::getNextLevelXP() const {
    return calculateLevelXPRequirement();
}

void XP::saveToFile(std::ofstream& file) const {
    if (file) {
        file << SAVE_FILE_HEADER << " " << level << " " << experience << "\n";
    }
}

void XP::loadFromFile(std::ifstream& file) {
    std::string header;
    if (file >> header >> level >> experience) {
        if (header != SAVE_FILE_HEADER) {
            level = 1;
            experience = 0;
        }
    }
    else {
        level = 1;
        experience = 0;
    }
}

int XP::calculateLevelXPRequirement() const {
    if (level <= HIGH_LEVEL_THRESHOLD) {
        return level * BASE_XP_PER_LEVEL;
    }
    return (level + HIGH_LEVEL_XP_BONUS) * BASE_XP_PER_LEVEL;
}