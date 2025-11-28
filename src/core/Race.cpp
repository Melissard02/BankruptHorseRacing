#include "../Race.h"
#include "Horse.h"
#include "Utils.h"

#include <algorithm>
#include <chrono>
#include <iomanip> // std::setw, std::left
#include <iostream>
#include <thread>
#include <vector>

Race::Race(std::vector<Horse>& horses)
    : horses(horses), progress(horses.size(), 0), winnerIndex(-1) {}

void Race::startRace() {
    // --- ICONS ---
    std::string horseIcon  = "🐎";
    std::string flagIcon   = "🏁";
    std::string trophyIcon = "🏆";
    std::string goldMedal  = "🥇";
    std::string silverMedal = "🥈";
    std::string bronzeMedal = "🥉";

    if (horses.empty()) {
        std::cout << "No horses in this race.\n";
        winnerIndex = -1;
        return;
    }

    const int TRACK_LENGTH = 50;
    progress.assign(horses.size(), 0);
    winnerIndex = -1;
    std::vector<int> finishedOrder;

    // --- SMOOTH SCREEN CLEAR (one time only) ---
    std::cout << "\x1b[2J\x1b[H";

    std::cout << flagIcon << " THE BANKRUPT DERBY BEGINS! " << flagIcon << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    bool allFinished = false;
    int round = 0;

    // Height of printed area, so we can safely redraw over it
    int frameHeight = static_cast<int>(horses.size()) + 6;

    while (!allFinished) {
        allFinished = true;
        round++;

        // --- UPDATE PROGRESS ---
        for (size_t i = 0; i < horses.size(); ++i) {
            if (progress[i] < TRACK_LENGTH) {
                allFinished = false;

                double gainRaw =
                    horses[i].getSpeed() * 0.05 +
                    horses[i].getStamina() * 0.03 +
                    horses[i].getLuck() * 0.02;

                int boost = getRandom(1, 4);
                int gain = static_cast<int>(gainRaw / 2 + boost);

                if (progress[i] > TRACK_LENGTH / 2)
                    gain = std::max(1, gain - getRandom(0, 2));

                progress[i] = std::min(progress[i] + gain, TRACK_LENGTH);

                if (progress[i] >= TRACK_LENGTH &&
                    std::find(finishedOrder.begin(), finishedOrder.end(), i) == finishedOrder.end()) {
                    finishedOrder.push_back(static_cast<int>(i));
                }
            }
        }

        // --- SMOOTH FRAME REFRESH (NO FLICKER!) ---
        std::cout << "\x1b[H";  // Move cursor to top-left

        // --- DRAW HEADER ---
        std::cout << flagIcon << " BANKRUPT DERBY " << flagIcon << "\n";
        std::cout << std::string(TRACK_LENGTH + 22, '-') << "\n";

        // --- DRAW EACH HORSE ---
        for (size_t i = 0; i < horses.size(); ++i) {

            // Build track
            int pos = std::min(progress[i], TRACK_LENGTH - 1);
            std::string track(TRACK_LENGTH, '-');
            track += "|"; // finish line marker
            track.replace(pos, 1, horseIcon);

            // Medal assignment
            std::string medal = "";
            auto it = std::find(finishedOrder.begin(), finishedOrder.end(), i);
            if (it != finishedOrder.end()) {
                int place = std::distance(finishedOrder.begin(), it);
                if (place == 0) medal = goldMedal + " ";
                else if (place == 1) medal = silverMedal + " ";
                else if (place == 2) medal = bronzeMedal + " ";
            }

            std::ostringstream nameField;
            nameField << medal << horses[i].getName();

            std::cout << std::left << std::setw(22)
                      << nameField.str()
                      << " | " << track << "\n";
        }

        std::cout << std::string(TRACK_LENGTH + 22, '-') << "\n";
        std::cout << "Round " << round << "\n";

        // --- Smooth frame pacing ---
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    // --- SHOW WINNER ---
    if (!finishedOrder.empty())
        winnerIndex = finishedOrder[0];

    std::cout << "\n" << trophyIcon << " Winner: "
              << horses[winnerIndex].getName() << "!\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
}



int Race::getWinnerIndex() const {
    return winnerIndex;
}