#ifndef CHARACTER_H  
#define CHARACTER_H

#include <iostream>

class Character {
public:
    Character(int hp, int damage, int hard_damage, int defense);

    void TakeDamage(int damage);

    int GetHP() const;
    int GetDamage() const;
    int GetDefense() const;
    int GetHardDamage() const;

protected:
    int HP;
    int Damage;
    int Defense;
    int Hard_Damage;
};

#endif 