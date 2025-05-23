// Abyss_of_Choice.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "XP.h"
#include "Character.h"
#include "player.h"
#include "Enemy.h"
#include "BattleEvent.h"
#include "PlayerInventory.h"
#include "Inventory.h"


int main() {



    Player player(100, 20,30, 5,2); 
    player.equipItem(Inventory::SWORD,  "Dragon Slayer", 0, 0, 0, 0 );
    player.equipItem(Inventory::HELMET,  "Iron Helmet", 0, 0, 0, 0 );


    BattleEvent event(player); // Создаем событие с игроком

    // Добавляем врагов в событие
    // std::cout << player.getHP() << std::endl;
    event.addEnemy(Enemy(100, 15,25, 1, 100,100)); // Гоблин
    // std::cout << player.getHP() << std::endl;
    event.addEnemy(Enemy(80, 10,25, 2, 150,100)); // Орк
    //std::cout << player.getHP() << std::endl;
    event.addEnemy(Enemy(120, 10,25, 5, 200,100)); // Тролль

    //std::cout << player.getHP() << std::endl;

    // Начинаем событие
    event.start();
    player.heal(player.getMaxHp());
    BattleEvent event2(player);
    event2.addEnemy(Enemy(200, 15, 25, 1, 100, 100)); // Гоблин
    event2.addEnemy(Enemy(280, 10, 25, 2, 150, 100)); // Орк
    event2.addEnemy(Enemy(320, 10, 25, 5, 200, 100)); // Тролль

    event2.start();
    player.heal(player.getMaxHp());
    return 0;
}