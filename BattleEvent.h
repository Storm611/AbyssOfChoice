#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include <cstdlib> 
#include <ctime>   
class BattleEvent {
public:
    BattleEvent(Player& player) : player(player) {}

    void addEnemy(const Enemy& enemy) {
        enemies.push_back(enemy);
    }

    void start() {
        for (auto& enemy : enemies) {
            // std::cout << "A wild " << "Enemy appears!" << std::endl;
            battle(enemy);

            if (player.getHP() <= 0) {
                // std::cout << "Player has been defeated!" << std::endl;
                break; // ���� ����� �����, ������� �� �����
            }

        }
    }

private:
    void battle(Enemy& enemy) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        std::cout << "A wild enemy appears!" << std::endl;

        while (enemy.getHP() > 0 && player.getHP() > 0) {
            // ����� �������� ���������
            std::cout << "\nPlayer HP: " << player.getHP() << "/" << player.getMaxHp()
                << " | Enemy HP: " << enemy.getHP() << std::endl;

            // ���� ������ �����
            std::cout << "Choose attack type:\n"
                << "1. Normal attack (" << player.getDamage() << " damage)\n"
                << "2. Heavy attack (" << player.getHardDamage() << " damage)\n"
                << "3 Heal by health potion (40%)\n"
                << "Your choice: ";

            int choice;
            std::cin >> choice;
            float chance = 0;
            float multiplier = 1.0f;
            // ��������� ������ ������
            switch (choice) {
            case 1: // ������� �����
                enemy.takeDamage(player.getDamage());
                std::cout << "You hit the enemy for " << player.getDamage() << " damage!\n";
                break;
            case 2: // ������� �����
                chance = 25 + (rand() % 150);
                multiplier = chance / 100.0f;

                enemy.takeDamage(player.getHardDamage() * multiplier);
                std::cout << "You deliver a heavy blow for " << player.getHardDamage() * multiplier << " damage!\n";

                break;
            case 3: // ������������� �����
                if (player.useHealthPotion()) {
                    std::cout << "You used a health potion and recovered 40% of your max HP!\n";
                    std::cout << "Current HP: " << player.getHP() << "/" << player.getMaxHp() << "\n";
                }
                else {
                    std::cout << "You have no health potions left!\n";
                }
                break;
            default:
                std::cout << "Invalid choice! You hesitate and miss your turn.\n";
                break;
            }

            // ���������, ��� �� ����
            if (enemy.getHP() <= 0) {
                std::cout << "Enemy defeated!\n";
                break;
            }

            // ��� �����
            player.takeDamage(enemy.getDamage());
            std::cout << "Enemy attacks you for " << enemy.getDamage() << " damage!\n";

            // ���������, ��� �� �����
            if (player.getHP() <= 0) {
                std::cout << "You have been defeated!\n";
                break;
            }
        }

        // ������� �� ������
        if (enemy.getHP() <= 0) {
            player.gainExperience(enemy.getExperienceReward());
            player.gainMoney(enemy.getMoneyReward());
            std::cout << "Gained " << enemy.getExperienceReward() << " XP and "
                << enemy.getMoneyReward() << " gold!\n";
        }

        
    }
    Player& player; // ������ �� ������
    std::vector<Enemy> enemies; // ������ ������


};