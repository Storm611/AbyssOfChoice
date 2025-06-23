#include "XP.h"

XP::XP() : experience(0), level(1) {}

void XP::addExperience(int exp) {
    experience += exp;
}

bool XP::checkLevelUp() {
    if (experience >= (level * 100)) {
        return true;
    }
    return false;
}

void XP::levelUp() {
    int x = level;
    if (x > 10) {
        x = x + 7;
    }
    experience -= (x * 100);
    level++;
}

int XP::getLevel() const {
    return level;
}

void XP::saveToFile(std::ofstream& file) const {
    file << "XP " << level << " " << experience << "\n";
}

void XP::loadFromFile(std::ifstream& file) {
    std::string xpHeader;
    file >> xpHeader >> level >> experience;

    if (xpHeader != "XP") {
        level = 1;
        experience = 0;
    }
}