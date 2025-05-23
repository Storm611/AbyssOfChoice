#pragma once
class XP {
public:
    XP() : experience(0), level(1) {}

    void addExperience(int exp) {
        experience += exp;
    }

    bool checkLevelUp() {


        // ���������, ���������� �� ����� ��� ��������� ������
        if (experience >= (level * 100)) {
            return true; // ������� ����� ��������
        }
        return false; // ������� ������ ��������
    }

    void levelUp() {
        // ����������� ������� � ���������� ����������� ����
        int x = level; // ��������� ���������� �� ��������� ������
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

