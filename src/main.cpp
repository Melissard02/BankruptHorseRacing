#include "LoadScreen.h"
#include "Database.h"
#include "GameSave.h"
#include "Better.h"
#include "Horse.h"
#include "Menu.h"
#include "Player.h"
#include "Race.h"
#include "Utils.h"
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif
/* =============================
 * ----------  HELPER FUNCTIONS  --------
 * =============================*/
static GameSave buildSave(const Player& player, const Bank& bank, const std::vector<Horse>& horses) {
    GameSave s;
    s.playerName = player.getName();
    s.balance = player.getBalance();
    s.savings = bank.getSavings();
    s.income = player.getIncome();
    s.bets = player.getBets();
    s.betAmount = player.getBetAmount();
    s.betHorseIndex = player.getBetHorseIndex();

    s.horses.clear();
    s.horses.reserve(horses.size());

    for (const auto& h : horses) {
        HorseSave hs;
        hs.horseName = h.getName();
        hs.legendary = h.isLegendary();
        hs.speed = h.getSpeed();
        hs.stamina = h.getStamina();
        hs.popularity = h.getPopularity();
        hs.luck = h.getLuck();
        hs.wins = h.getWins();
        hs.races = h.getRaces();
        s.horses.push_back(hs);
    }
    return s;
}

static void applySave(const GameSave& s, Player& playerOut, Bank& bankOut, std::vector<Horse>& horsesOut) {
    playerOut = Player(s.playerName, s.balance, s.income);

    bankOut.setSavings(s.savings);

    horsesOut.clear();
    horsesOut.reserve(s.horses.size());

    for (const auto& hs : s.horses) {
        Horse h(hs.horseName, hs.legendary);
        h.setLoadedData(hs.speed, hs.stamina, hs.popularity, hs.luck, hs.wins, hs.races);
        horsesOut.push_back(h);
    }
}

/* =============================
 * -------------------  MAIN  ------------------------
 * =============================*/
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // --- LOAD SCREEN OBJECT ---
    LoadScreen lScreen;

    // OBJECTS
    Player player("cool dude", 500, 100);
    Bank bank;
    std::vector<Horse> horses;

    bool legendarySpawned = false;
    std::string legendaryName;

    bool startedGame = false;
    while (!startedGame) {
        int startChoice = lScreen.loadScreen();

        if (startChoice == 1) {
            // NEW GAME
            std::string playerName = lScreen.newGame();
            player = Player(playerName, 500, 100);
            bank.setSavings(1000);

            horses = {
                Horse("Thunder"),
                Horse("Cracker"),
                Horse("Flash"),
                Horse("Lantern"),
                Horse("Werthers"),
                Horse("Seltzer"),
                Horse("Pumpkin"),
                Horse("Echo")
            };
            for (auto& h : horses) h.generateStats();

            // Legendary spawn
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

                Horse legendaryHorse = legendaries[getRandom(0, static_cast<int>(legendaries.size()) - 1)];
                legendaryHorse.generateStats();
                legendaryName = legendaryHorse.getName();
                horses.push_back(legendaryHorse);
                legendarySpawned = true;
            }
            startedGame = true;
        } else if (startChoice == 2) {
            // LOAD GAME
            bool loaded = lScreen.loadGame();
            if (!loaded) {
                continue;
            }

            applySave(lScreen.getSave(), player, bank, horses);

            legendarySpawned = false;
            legendaryName.clear();

            startedGame = true;
        } else if (startChoice == 0) {
            return 0;
        } else {
            continue;
        }
    }


    // --- NPC BETTERS ---
    std::vector<Better> npcs = {
        Better("Candle", 300),
        Better("Mentos", 200),
        Better("Propel", 1000),
        Better("Mr. Monopoly", 1000000)
    };

    // --- MENUS ---
    Race race(horses);
    Menu menu;

    Database database;
    database.initializeSchema();

    bool running = true;

    while (running) {
        int choice = menu.mainMenu();
        switch (choice) {
        case 1:
            menu.playerMenu(player, horses, bank);
            break;
        case 2:
            menu.betMenu(player, horses);
            break;
        case 3:
            menu.horseMenu(horses);
            break;
        case 4:
            menu.bankMenu(player, bank);
            break;
        case 5:
            race = Race(horses);
            menu.raceMenu(race, horses, player, npcs, legendarySpawned, legendaryName);
            break;
        case 0:
            database.saveGame(buildSave(player, bank, horses));
            running = false;
            break;
        default:
            break;
        }
    }

    std::cout << "\nThanks for playing, " << player.getName() << "!\n";
    return 0;
}
