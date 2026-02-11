#include "core/Better.h"
#include "core/Horse.h"
#include "core/Player.h"
#include "core/Race.h"
#include "core/Utils.h"
#include "core/Bank.h"

#include "ui/tui/TuiMainMenu.h"
#include "ui/tui/TuiPlayerMenu.h"
#include "ui/tui/TuiHorseMenu.h"
#include "ui/tui/TuiBettingMenu.h"
#include "ui/tui/TuiBankMenu.h"
#include "ui/tui/TuiRaceMenu.h"

#include <iostream>
#include <vector>

#include <ftxui/component/screen_interactive.hpp>

int main() {
    using namespace ftxui;

    // =============================================================
    // CREATE ONE GLOBAL SCREEN (THIS FIXES ENTER NOT WORKING)
    // =============================================================
    auto screen = ScreenInteractive::TerminalOutput();

    // =============================================================
    // PLAYER
    // =============================================================
    Player player = Player::loadFromFile("player.txt");

    // =============================================================
    // HORSES
    // =============================================================
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

    for (auto& h : horses)
        h.generateStats();

    // Legendary spawn logic
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

    // =============================================================
    // NPC BETTORS
    // =============================================================
    std::vector<Better> npcs = {
        Better("Candle", 300),
        Better("Mentos", 200),
        Better("Propel", 1000),
        Better("Mr. Monopoly", 1000000)
    };

    // =============================================================
    // BANK
    // =============================================================
    Bank bank(player);

    // =============================================================
    // CREATE ALL MENUS — NOW PASSING THE SHARED SCREEN
    // =============================================================
    IMainMenu* mainMenu =
        new TuiMainMenu(screen, player, horses, bank, npcs);

    IPlayerMenu* playerMenu =
        new TuiPlayerMenu(screen, player, horses, bank);

    IHorseMenu* horseMenu =
        new TuiHorseMenu(screen, horses);

    IBetMenu* betMenu =
        new TuiBettingMenu(screen, player, horses);

    IBankMenu* bankMenuUI =
        new TuiBankMenu(screen, player, bank);

    IRaceMenu* raceMenu =
        new TuiRaceMenu(screen, player, horses, npcs, legendarySpawned, legendaryName);

    // =============================================================
    // MAIN LOOP
    // =============================================================
    bool running = true;

    while (running) {
        screen.Clear();
        int choice = mainMenu->mainMenu();

        switch (choice) {
            case 0: playerMenu->playerMenu(); break;
            case 1: betMenu->betMenu(); break;
            case 2: horseMenu->horseMenu(); break;
            case 3: bankMenuUI->bankMenu(); break;
            case 4: raceMenu->raceMenu(); break;
            case 5:
                player.saveToFile("player.txt");
                running = false;
                break;
        }
    }

    std::cout << "\nThanks for playing, " << player.getName() << "!\n";

    // =============================================================
    // CLEANUP
    // =============================================================
    delete mainMenu;
    delete playerMenu;
    delete betMenu;
    delete horseMenu;
    delete bankMenuUI;
    delete raceMenu;

    return 0;
}
