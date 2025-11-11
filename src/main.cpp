#include <iostream>
#include <vector>
#include "Menu.h"
#include "Player.h"
#include "Horse.h"
#include "Race.h"

int main() {
    // --- create player and horses ---
    Player player("Melissa", 500, 100);

    std::vector<Horse> horses = {
        Horse("Thunder"),
        Horse("Cracker"),
        Horse("Flash")
    };
    for (auto& h : horses) {
        h.generateStats();
    }

    // --- start menu system ---
    Race race(horses);
    Menu menu;
    bool running = true;

    while (running) {
        int choice = menu.mainMenu();
        switch (choice) {
        case 1:
            menu.playerMenu(player);
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
            menu.raceMenu(race, horses);
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
