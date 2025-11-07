#include "Race.h"
#include "Utils.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>  // std::setw, std::left

Race::Race(const std::vector<Horse>& horses)
    : horses(horses), progress(horses.size(), 0), winnerIndex(-1) {}

void Race::startRace(int rounds) {
    if (horses.empty()) {
        std::cout << "No horses in this race.\n";
        winnerIndex = -1;
        return;
    }

    // Figure out name column width for clean alignment
    size_t nameWidth = 0;
    for (const auto& h : horses) {
        if (h.getName().size() > nameWidth) nameWidth = h.getName().size();
    }

    std::cout << "\n🏁 Race starting! (" << horses.size() << " horses)\n";

    // Scale so bars stay readable in console
    const int TRACK_SCALE = 12; // bigger = shorter bars

    for (int r = 1; r <= rounds; r++) {
        std::cout << "\nRound " << r << ":\n";

        for (size_t i = 0; i < horses.size(); ++i) {
            // Stat-based movement + a little randomness
            // Heavier weight on speed; stamina next; luck small; plus random boost
            int boost = getRandom(1, 10);
            int gain  = static_cast<int>(
                horses[i].getSpeed()   * 0.6 +
                horses[i].getStamina() * 0.3 +
                horses[i].getLuck()    * 0.1 +
                boost
            );

            progress[i] += gain;

            int barLen = progress[i] / TRACK_SCALE;
            if (barLen < 0) barLen = 0;
            std::string bar(static_cast<size_t>(barLen), '-');

            std::cout << std::left << std::setw(static_cast<int>(nameWidth))
                      << horses[i].getName()
                      << " | " << bar << "🏇\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }

    // Determine winner by max progress
    winnerIndex = 0;
    for (size_t i = 1; i < progress.size(); ++i) {
        if (progress[i] > progress[winnerIndex]) winnerIndex = static_cast<int>(i);
    }

    std::cout << "\n🎉 Winner: " << horses[winnerIndex].getName() << "!\n";
}

int Race::getWinnerIndex() const {
    return winnerIndex;
}
