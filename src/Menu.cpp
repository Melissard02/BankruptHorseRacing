#include "Menu.h"
#include "Player.h"
#include "Horse.h"
#include "Race.h"
#include <iostream>
#include <vector>
#include <limits>

// ---------------------- Utility ----------------------
void Menu::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ---------------------- MAIN MENU ----------------------
int Menu::mainMenu() const {
    clearScreen();
    std::cout << "=== BANKRUPT RACING ===\n";
    std::cout << "1. Player Info\n";
    std::cout << "2. Betting\n";
    std::cout << "3. Horse\n";
    std::cout << "4. Bank\n";
    std::cout << "5. Start Race\n";
    std::cout << "0. Exit\n";
    std::cout << "\nSelect: ";

    int choice{};
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

// ---------------------- PLAYER MENU ----------------------
void Menu::playerMenu(const Player &player) const {
    while (true) {
        clearScreen();
        std::cout << "=== PLAYER ===\n";
        std::cout << "Name:    " << player.getName() << "\n";
        std::cout << "Balance: $" << player.getBalance() << "\n";
        std::cout << "Income:  $" << player.getIncome() << "\n";

        int betAmt = player.getBetAmount();
        int betIdx = player.getBetHorseIndex();

        if (betIdx >= 0 && betAmt > 0) {
            std::cout << "Current Bet: $" << betAmt
                      << " on horse index " << betIdx << "\n";
        } else {
            std::cout << "Current Bet: (none)\n";
        }

        std::cout << "\n0. Return\n";
        std::cout << "Select: ";

        int choice{};
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
            break;
    }
}

// ---------------------- BETTING MENU ----------------------
void Menu::betMenu(Player &player, const std::vector<Horse> &horses) const {
    while (true) {
        clearScreen();
        std::cout << "=== BETTING ===\n";
        std::cout << "1. View Horses\n";
        std::cout << "2. Place Bet\n";
        std::cout << "0. Return\n";
        std::cout << "Select: ";

        int choice{};
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
            break;

        if (choice == 1) {
            clearScreen();
            for (const auto &horse : horses) {
                horse.displayStats();
            }
            std::cout << "\nPress Enter to return.";
            std::cin.get();
        } else if (choice == 2) {
            clearScreen();
            std::cout << "Horse List:\n";
            for (size_t i = 0; i < horses.size(); i++) {
                std::cout << "[" << (i + 1) << "] " << horses[i].getName() << "\n";
            }
            std::cout << "Enter horse number to bet on: ";
            int horseIndex;
            std::cin >> horseIndex;
            horseIndex--;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (horseIndex < 0 || horseIndex >= static_cast<int>(horses.size())) {
                std::cout << "Invalid horse selection!\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }


            std::cout << "Enter bet amount: ";
            int amount;
            std::cin >> amount;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (player.placeBet(amount, horseIndex)) {
                std::cout << "Bet placed successfully on "
                          << horses[horseIndex].getName()
                          << " for $" << amount << "!\n";
            } else {
                std::cout << "Failed to place bet.\n";
            }

            std::cout << "\nPress Enter to return.";
            std::cin.get();
        }
    }
}

// ---------------------- HORSE MENU ----------------------
void Menu::horseMenu(const std::vector<Horse> &horses) const {
    while (true) {
        clearScreen();
        std::cout << "=== HORSE ===\n";
        std::cout << "1. Horse List\n";
        std::cout << "2. View Stats\n";
        std::cout << "0. Return\n";
        std::cout << "Select: ";

        int choice{};
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
            break;

        clearScreen();
        if (horses.empty()) {
            std::cout << "If this shows up something is very wrong\n";
        } else if (choice == 1) {
            std::cout << "Horse List:\n";
            for (size_t i = 0; i < horses.size(); i++) {
                std::cout << "[" << (i + 1) << "] " << horses[i].getName() << "\n";
            }
        } else if (choice == 2) {
            for (const auto &horse : horses) {
                horse.displayStats();
            }
        } else {
            std::cout << "Invalid Selection!\n";
        }

        std::cout << "\nPress Enter to return\n";
        std::cin.get();
    }
}

// ---------------------- BANK MENU ----------------------
void Menu::bankMenu(const Player &player) const {
    while (true) {
        clearScreen();
        std::cout << "=== BANK ===\n";
        std::cout << "Balance: $" << player.getBalance() << "\n";
        std::cout << "Income:  $" << player.getIncome() << "\n";
        std::cout << "0. Return\n";
        std::cout << "Select: ";

        int choice{};
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
            break;

        std::cout << "Future logic will be here. Press Enter";
        std::cin.get();
    }
}

// ---------------- RACE MENU -------------------------
void Menu::raceMenu(Race &race, const std::vector<Horse>& horses) const {
    while (true) {
        clearScreen();
        std::cout << "=== RACE ===\n";
        std::cout << "\nFeatured Racers:\n";
        for (size_t i = 0; i < horses.size(); i++) {
            std::cout << "[" << (i + 1) << "] " << horses[i].getName() << "\n";
        }

        std::cout << "\n1. Start Race\n";
        std::cout << "0. Return\n";



        int choice{};
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            break;
        }
        if (choice == 1) {
            clearScreen();
            race.startRace();
            int winner = race.getWinnerIndex();

            std::cout << "\n Winner: " << horses[winner].getName() << "!\n";
            std::cout << "\nPress enter to return.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

        }
    }
}
