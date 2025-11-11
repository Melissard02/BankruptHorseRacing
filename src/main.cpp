#include "Better.h"
#include "Horse.h"
#include "Menu.h"
#include "Player.h"
#include "Race.h"
#include "Better.h"
#include <iostream>
#include <vector>

int main() {
    // --- CREATE PLAYER ---
    Player player("Melissa", 500, 100);

    // --- CREATE HORSES ---
    std::vector<Horse> horses = {
        Horse("Thunder"),
        Horse("Cracker"),
        Horse("Flash")
    };
    for (auto& h : horses) {
        h.generateStats();
    }

    // --- CREATE NPC BETTERS ---
    std::vector<Better> npcs = {
        Better("Candle", 300),
        Better("Mentos", 200),
        Better("Propel", 1000),
        Better("Mr. Monopoly", 1000000)
    };

    // --- start menu system ---
    Race race(horses);
    Menu menu;
    bool running = true;

    while (running) {
        int choice = menu.mainMenu();
        switch (choice) {
        case 1:
            menu.playerMenu(player, horses);
            break;
        case 2:
            menu.betMenu(player, horses);
            break;
        case 3:
            menu.horseMenu(horses);
            break;
        case 4:
            menu.bankMenu(player);
            break;
        case 5:
            menu.raceMenu(race, horses, player, npcs);
            break;
        case 0:
            running = false;
            break;
        default:
            break;
        }
    }

    std::cout << "\nThanks for playing, " << player.getName() << "!\n";
    return 0;
}
