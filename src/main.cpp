#include "core/Better.h"
#include "core/Horse.h"
#include "core/Player.h"
#include "core/Race.h"
#include "core/Utils.h"

#include "ui/tui/TuiMainMenu.h"
#include "ui/tui/TuiPlayerMenu.h"
#include "ui/tui/TuiHorseMenu.h"
#include "ui/tui/TuiBettingMenu.h"
#include "ui/tui/TuiBankMenu.h"
#include "ui/tui/TuiRaceMenu.h"

#include <iostream>
#include <vector>

int main() {

    // --- CREATE PLAYER ---
    Player player = Player::loadFromFile("player.txt");

    // --- CREATE HORSES ---
    std::vector<Horse> horses = {
        Horse("Thunder"),
        Horse("Cracker"),
        Horse("Flash"),
        Horse("Lantern"),
        Horse("Werthers"),
        Horse("Seltzer"),
        Horse("Pumpkin"),
        Horse("Echo")
    };
    for (auto& h : horses) {
        h.generateStats();
    }

    // --- LEGENDARY HORSES ---
    bool legendarySpawned = false;
    std::string legendaryName;

    if (getRandom(1, 100) <= 5) {
        std::vector<Horse> legendaries = {
            Horse("Seabiscuit", true),
            Horse("Shadowfax", true),
            Horse("Spirit", true),
            Horse("Twilight Sparkle", true),
            Horse("Epona", true),
            Horse("Potoooooooo", true),
            Horse("Spamton G. Spamton", true),
        };

        Horse legendaryHorse = legendaries[getRandom(0, legendaries.size() - 1)];
        legendaryHorse.generateStats();
        legendaryName = legendaryHorse.getName();
        horses.push_back(legendaryHorse);
        legendarySpawned = true;
    }

    // --- CREATE NPC BETTERS ---
    std::vector<Better> npcs = {
        Better("Candle", 300),
        Better("Mentos", 200),
        Better("Propel", 1000),
        Better("Mr. Monopoly", 1000000)
    };

    // --- CREATE BANK ---
    Bank bank(player);

    // ------------------------------------------------------------------------------
    // --- CREATE ALL TUI MENUS
    // ------------------------------------------------------------------------------
    IMainMenu* mainMenu =
        new TuiMainMenu(player, horses, bank, npcs);

    IPlayerMenu* playerMenu =
        new TuiPlayerMenu(player, horses, bank);

    IHorseMenu* horseMenu =
        new TuiHorseMenu(horses);

    IBetMenu* betMenu =
        new TuiBettingMenu(player, horses);

    IBankMenu* bankMenu =
        new TuiBankMenu(player, bank);

    IRaceMenu* raceMenu =
        new TuiRaceMenu(player, horses, npcs, legendarySpawned, legendaryName);

    // ------------------------------------------------------------------------------
    // MAIN GAME LOOP
    // ------------------------------------------------------------------------------
    bool running = true;

    while (running) {
        int choice = mainMenu->mainMenu();
        switch (choice) {
            case 1: playerMenu->playerMenu(); break;
            case 2: betMenu->betMenu(); break;
            case 3: horseMenu->horseMenu(); break;
            case 4: bankMenu->bankMenu(); break;
            case 5: raceMenu->raceMenu(); break;

            case 0: {
                player.saveToFile("player.txt");
                running = false;
            } break;
        }
    }

    // --- CLEAN UP ---
    delete mainMenu;
    delete playerMenu;
    delete betMenu;
    delete horseMenu;
    delete bankMenu;
    delete raceMenu;

    return 0;
}