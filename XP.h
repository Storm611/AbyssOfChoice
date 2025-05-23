#pragma once
class XP {
public:
    XP() : experience(0), level(1) {}

    void addExperience(int exp) {
        experience += exp;
    }

    bool checkLevelUp() {


        // Проверяем, достаточно ли опыта для повышения уровня
        if (experience >= (level * 100)) {
            return true; // Уровень можно повысить
        }
        return false; // Уровень нельзя повысить
    }

    void levelUp() {
        // Увеличиваем уровень и сбрасываем необходимый опыт
        int x = level; // Замедляем прогрессию от улучшение уровня
        if (x > 10)
        {

            x = x + 7;

        }
        experience -= (x * 100);
        level++;
    }
    int getLevel() const { return level; }

private:
    int experience;
    int level;
};

