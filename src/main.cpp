#include <iostream>
#include <vector>
#include "Horse.h"
#include "Player.h"
#include "Race.h"

int main() {
    std::cout << "==== TESTING: HORSE CLASS ====\n";
    Horse h("Thunder");
    h.generateStats();
    h.displayStats();
    h.addRaceResult(true);   // simulate a win
    h.displayStats();

    std::cout << "\n==== TESTING: PLAYER CLASS ====\n";
    Player p("Melissa", 500, 100);
    std::cout << "Player: " << p.getName() << "\n";
    std::cout << "Balance: $" << p.getBalance() << "\n";
    p.placeBet(50);
    std::cout << "Balance after bet: $" << p.getBalance() << "\n";

    std::cout << "\n==== TESTING: RACE CLASS ====\n";
    std::vector<Horse> horses = {
        Horse("Lightning"),
        Horse("Thunder"),
        Horse("Biscuit")
    };

    // Generate stats for each horse
    for (auto& horse : horses) {
        horse.generateStats();
        horse.displayStats();
    }

    Race race(horses);
    race.startRace();

    int winner = race.getWinnerIndex();
    std::cout << "Winner: " << horses[winner].getName() << "\n";

    return 0;
}
