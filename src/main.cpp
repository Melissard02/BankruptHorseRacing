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
static GameSave buildSave(const Player& player, const std::vector<Horse>& horses) {
    GameSave s;
    s.playerName = player.getName();
    s.balance = player.getBalance();
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

static void applySave(const GameSave& s, Player& playerOut, std::vector<Horse>& horsesOut) {
    playerOut = Player(s.playerName, s.balance, s.income);

    // Optional: only if you add a Player setter:
    // playerOut.setBetState(s.bets, s.betAmount, s.betHorseIndex);

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

    // --- CREATE PLAYER ---
    LoadScreen lScreen;
    std::string playerName = lScreen.newGame();
    Player player(playerName, 500, 100);

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

    // --- start menu system ---
    Race race(horses);
    Menu menu;
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
            player.saveToFile("player.txt");
            running = false;
            break;
        default:
            break;
        }
    }

    std::cout << "\nThanks for playing, " << player.getName() << "!\n";
    return 0;
}
