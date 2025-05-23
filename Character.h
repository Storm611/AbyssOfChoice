#pragma once
#include "iostream"
class Character 
{
public:
    Character(int hp, int damage, int hard_damage, int defense)
        : HP(hp), Damage(damage), Hard_Damage(hard_damage), Defense(defense) {}

    void takeDamage(int damage)
    {
        int effectiveDamage = damage - Defense;
        if (effectiveDamage > 0)
        {
            HP -= effectiveDamage;
        }
    }

    int getHP() const { return HP; }
    int getDamage() const { return Damage; }
    int getDefense() const { return Defense; }
    int getHardDamage() const { return Hard_Damage; }



protected:
    int HP;
    int Damage;
    int Defense;
    int Hard_Damage;
};