#include "BattleEvent.h"

BattleEvent::BattleEvent(Player& player) : player(player) {}

void BattleEvent::addEnemy(const Enemy& enemy) {
    enemies.push_back(enemy);
}

void BattleEvent::start() {
    for (auto& enemy : enemies) {
        battle(enemy);

        if (player.GetHP() <= 0) {
            break;
        }
    }
}

void BattleEvent::battle(Enemy& enemy) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::cout << "A wild enemy appears!" << std::endl;

    while (enemy.GetHP() > 0 && player.GetHP() > 0) {
        std::cout << "\nPlayer HP: " << player.GetHP() << "/" << player.GetMaxHp()
            << " | Enemy HP: " << enemy.GetHP() << std::endl;

        std::cout << "Choose attack type:\n"
            << "1. Normal attack (" << player.GetDamage() << " damage)\n"
            << "2. Heavy attack (" << player.GetHardDamage() << " damage)\n"
            << "3 Heal by health potion (40%)\n"
            << "Your choice: ";

        int choice;
        std::cin >> choice;
        float chance = 0;
        float multiplier = 1.0f;

        switch (choice) {
        case 1:
            enemy.TakeDamage(player.GetDamage());
            std::cout << "You hit the enemy for " << player.GetDamage() << " damage!\n";
            break;
        case 2:
            chance = 25 + (rand() % 150);
            multiplier = chance / 100.0f;
            enemy.TakeDamage(player.GetHardDamage() * multiplier);
            std::cout << "You deliver a heavy blow for " << player.GetHardDamage() * multiplier << " damage!\n";
            break;
        case 3:
            if (player.UseHealthPotion()) {
                std::cout << "You used a health potion and recovered 40% of your max HP!\n";
                std::cout << "Current HP: " << player.GetHP() << "/" << player.GetMaxHp() << "\n";
            }
            else {
                std::cout << "You have no health potions left!\n";
            }
            break;
        default:
            std::cout << "Invalid choice! You hesitate and miss your turn.\n";
            break;
        }

        if (enemy.GetHP() <= 0) {
            std::cout << "Enemy defeated!\n";
            break;
        }

        player.TakeDamage(enemy.GetDamage());
        std::cout << "Enemy attacks you for " << enemy.GetDamage() << " damage!\n";

        if (player.GetHP() <= 0) {
            std::cout << "You have been defeated!\n";
            break;
        }
    }

    if (enemy.GetHP() <= 0) {
        player.GainExperience(enemy.GetExperienceReward());
        player.GainMoney(enemy.GetMoneyReward());
        std::cout << "Gained " << enemy.GetExperienceReward() << " XP and "
            << enemy.GetMoneyReward() << " gold!\n";
    }
}

