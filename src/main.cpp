#include "core/Better.h"
#include "core/Horse.h"
#include "core/Player.h"
#include "core/Race.h"
#include "core/Utils.h"
#include "ui/oldmenu/Menu.h"
#include "ui/oldmenu/TerminalMenu.h"
#include "ui/tui/UI.h"

#include <bits/this_thread_sleep.h>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

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

    UI* ui = nullptr;

    // Temporary use of the old menu system
    ui = new TerminalMenu(player, horses, bank, npcs);

    bool running = true;

    while (running) {
        int choice = ui->mainMenu();
        switch (choice) {
            case 1: ui->playerMenu(); break;
            case 2: ui->betMenu(); break;
            case 3: ui->horseMenu(); break;
            case 4: ui->bankMenu(); break;

            case 5: {
                Race race(horses);
                ui->raceMenu();
            } break;

            case 0: {
                player.saveToFile("player.txt");
                running = false;
            } break;
        }
    }

    std::cout << "\nThanks for playing, " << player.getName() << "!\n";

    delete ui; // cleanup
    return 0;
}