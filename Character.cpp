#include "Character.h"

Character::Character(int hp, int damage, int hard_damage, int defense)
    : HP(hp), Damage(damage), Hard_Damage(hard_damage), Defense(defense) {
}

void Character::TakeDamage(int damage) {
    int effectiveDamage = damage - Defense;
    if (effectiveDamage > 0) {
        HP -= effectiveDamage;
    }
}

int Character::GetHP() const { return HP; }
int Character::GetDamage() const { return Damage; }
int Character::GetDefense() const { return Defense; }
int Character::GetHardDamage() const { return Hard_Damage; }