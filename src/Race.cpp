#include "Race.h"
#include "Utils.h"
#include "Horse.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>  // std::setw, std::left
#include <vector>
#include <algorithm>

Race::Race(const std::vector<Horse>& horses)
    : horses(horses), progress(horses.size(), 0), winnerIndex(-1) {}

void Race::startRace() {
    std::string horseIcon = "🐎";
    std::string flagIcon  = "🏁";
    std::string trophyIcon = "🏆";

    if (horses.empty()) {
        std::cout << "No horses in this race.\n";
        winnerIndex = -1;
        return;
    }

    const int TRACK_LENGTH = 50; // number of steps from start to finish
    progress.assign(horses.size(), 0);
    winnerIndex = -1;
    std::vector<int> finishedOrder;

    std::cout << flagIcon << " THE BANKRUPT DERBY BEGINS! " << flagIcon << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    bool allFinished = false;
    int round = 0;

    while (!allFinished) {
        allFinished = true;
        ++round;

        // UPDATE HORSE PROGRESS
        for (size_t i = 0; i < horses.size(); ++i) {
            if (progress[i] < TRACK_LENGTH) {
                allFinished = false;
                int baseSpeed = horses[i].getSpeed();
                int baseStamina = horses[i].getStamina();
                int baseLuck = horses[i].getLuck();

                double rawGain = (baseSpeed * 0.05) + (baseStamina * 0.03) + (baseLuck * 0.02);
                int boost = getRandom(1, 4);
                int gain = static_cast<int>(rawGain / 2 + boost);

                if (progress[i] > TRACK_LENGTH / 2)
                    gain = std::max(1, gain - getRandom(0,2));

                progress[i] = std::min(progress[i] + gain, TRACK_LENGTH);
                if (progress[i] >= TRACK_LENGTH &&
                std::find(finishedOrder.begin(), finishedOrder.end(), i) == finishedOrder.end())
                {
                    finishedOrder.push_back(static_cast<int>(i));
                    int place = static_cast<int>(finishedOrder.size());

                    if (place == 1) horses[i].appendMedal("🥇");
                    else if (place == 2) horses[i].appendMedal("🥈");
                    else if (place == 3) horses[i].appendMedal("🥉");
                }
            }
        }

    // clear screen between frames
    #ifdef _WIN32
            system("cls");
    #else
            system("clear");
    #endif

        // DISPLAY THE TRACK
        std::cout << flagIcon <<" BANKRUPT DERBY "<< flagIcon <<" \n";
        std::cout << std::string(TRACK_LENGTH + 20, '-') << "\n";

        for (size_t i = 0; i < horses.size(); ++i) {
            int pos = std::min(progress[i], TRACK_LENGTH - 1);

            std::string track(TRACK_LENGTH, '-');
            track += "|";

            track.replace(pos, 1, horseIcon);

            // PRINT MEDAL NAME TRACK
            std::cout << std::left << std::setw(20)
            << horses[i].getName()
            << " | " << track << "\n";
        }

        std::cout << std::string(TRACK_LENGTH + 20, '-') << "\n";
        std::cout << "Round " << round << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // DETERMINE WINNER
    if (!finishedOrder.empty()) {
        winnerIndex = finishedOrder[0];
    } else {
        winnerIndex = -1;
    }

    std::cout << "\n" << trophyIcon <<" Winner: " << horses[winnerIndex].getName() << "!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    // CLEAR MEDALS FROM HORSE NAME
    for (auto& horse : horses) {
        horse.clearMedal();
    }
}


int Race::getWinnerIndex() const {
    return winnerIndex;
}