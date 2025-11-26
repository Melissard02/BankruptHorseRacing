#include "Menu.h"

#include "Bank.h"
#include "Better.h"
#include "Horse.h"
#include "Player.h"
#include "Race.h"
#include "Utils.h"

#include <iostream>
#include <limits>
#include <thread>
#include <vector>

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
void Menu::playerMenu(const Player &player, const std::vector<Horse> &horses) const {
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
                      << " on " << horses[betIdx].getName() << "\n";
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
            std::vector<int> bettableIndexes;
            for (size_t i = 0; i < horses.size(); i++) {
                if (!horses[i].isLegendary()) {
                    bettableIndexes.push_back(i);
                    std::cout << "[" << bettableIndexes.size() << "] "
                              << horses[i].getName() << "\n";
                }
            }

            if (bettableIndexes.empty()) {
                std::cout << "No eligible horses to bet on!\n";
                std::cout << "\nPress Enter to return.";
                std::cin.get();
                return;
            }

            std::cout << "Enter horse number to bet on: ";
            int choice;
            std::cin >> choice;
            choice--; // Convert to zero-based

            if (choice < 0 || choice >= static_cast<int>(bettableIndexes.size())) {
                std::cout << "Invalid horse selection!\n";
                std::cout << "\nPress Enter to return.";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            int horseIndex = bettableIndexes[choice]; // Map back to real index


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
void Menu::bankMenu(const Player &player, Bank &bank) const {
    while (true) {
        clearScreen();
        std::cout << "=== BANK ===\n";
        std::cout << "Checking: $" << player.getBalance() << "\n";
        std::cout << "Savings: $" << bank.getSavings() << "\n";
        std::cout << "Income:  $" << player.getIncome() << "\n";
        std::cout << "1. Deposit" << "\n";
        std::cout << "2. Withdraw" << "\n";
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
            std::cout << "Select Account to deposit to: " << "\n";
            std::cout << "1. Checking\n";
            std::cout << "2. Savings\n";

            int account{};
            std::cin >> account;
            if (account == 1) {
                int amt;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amt;

                bank.Deposit(amt, false);
            } else if (account == 2) {
                int amt;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amt;

                bank.Deposit(amt, true);
            }

        }
        if (choice == 2) {
            std::cout << "Select Account to withdraw from: " << "\n";
            std::cout << "1. Checking\n";
            std::cout << "2. Savings\n";

            int account{};
            std::cin >> account;
            if (account == 1) {
                int amt;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amt;

                bank.Withdraw(amt, false);
            } else if (account == 2) {
                int amt;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amt;

                bank.Withdraw(amt, true);
            }
        }

    }
}

// ---------------- RACE MENU -------------------------
void Menu::raceMenu(Race &race, const std::vector<Horse>& horses,
              Player &player, std::vector<Better>& npcs,
              bool legendarySpawned, const std::string& legendaryName) const {
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
            // Show announcement if there’s a legendary horse
            if (legendarySpawned) {
                std::cout << "\n⚡ A NEW CHALLENGER APPROACHES! ⚡\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "\nThe LEGENDARY horse " << legendaryName
                          << " has entered the race!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1200));
            }
        }

            std::cout << "=== BANKRUPT DERBY ===\n";
            std::cout << "\nCollecting Bets!\n";
            bool anyBets = false;


            // 💸 NPC betting loop
            for (auto& npc : npcs) {
                // filter out legendary horses first
                std::vector<int> bettableNPCs;
                for (size_t i = 0; i < horses.size(); i++) {
                    if (!horses[i].isLegendary()) {
                        bettableNPCs.push_back(i);
                    }
                }

                // skip NPCs if no valid horses or no funds
                if (bettableNPCs.empty() || npc.getBalance() < 50)
                    continue;

                int horse = bettableNPCs[npc.chooseRandomHorse(bettableNPCs.size())];
                int amount = npc.makeRandomBet(50, 150);

                std::cout << npc.getName() << " bets $" << amount
                          << " on " << horses[horse].getName() << "\n";

                anyBets = true;
            }

            if (!anyBets) {
                std::cout << "No other bets placed this round.\n";
            }

            std::cout << "\n All bets are in! Press ENTER to start the race...";
            std::cin.get();

            for (int i = 3; i > 0; --i) {
                clearScreen();
                std::cout << " THE RACE BEGINS IN . . . "<< i <<" \n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            clearScreen();
            std::cout << "GO!!!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));

            // 🏁 Start the race
            race.startRace();
            int winner = race.getWinnerIndex();

            std::cout << "\nWinner: " << horses[winner].getName() << "!\n";

            if (player.getBetHorseIndex() == winner) {
                int payout = player.getBetAmount() * 2;
                std::cout << "You won $" << payout << "!\n";
                player.addBalance(payout);
            } else if (player.getBetAmount() == 0) {
                std::cout << "You didn't place a bet.\n";
            } else {
                std::cout << "You lost your bet of $" << player.getBetAmount() << "!\n";
            }
            player.clearBet();

            // NPC payouts
            for (auto& npc : npcs) {
                if (npc.getBetHorseIndex() == winner) {
                    int payout = npc.getBetAmount() * 2;
                    npc.addBalance(payout);
                }
                npc.clearBet();
            }

            std::cout << "\nPress Enter to return.";
            std::cin.get();
        }
    }
