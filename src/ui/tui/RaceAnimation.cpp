#include "RaceAnimation.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

#include <thread>
#include <chrono>
#include <random>

using namespace ftxui;

RaceAnimation::RaceAnimation(ScreenInteractive& screen,
                                   Player& player,
                                   std::vector<Horse>& horses,
                                   std::vector<Better>& npcs,
                                   bool legendarySpawned,
                                   const std::string& legendaryName)
    : screen(screen), player(player), horses(horses), npcs(npcs),
      legendarySpawned(legendarySpawned), legendaryName(legendaryName) {}

void RaceAnimation::runRace() {
    const int raceLength = 50;
    std::vector<int> progress(horses.size(), 0);

    std::random_device rd;
    std::mt19937 rng(rd());

    auto layout = Renderer([&] {
        std::vector<Element> rows;

        for (int i = 0; i < (int)horses.size(); i++) {
            int pos = progress[i];
            pos = std::min(pos, raceLength);

            std::string bar = std::string(pos, '=') + "🐎";
            rows.push_back(text(horses[i].getName() + ": " + bar));
        }

        return vbox(rows);
    });

    screen.Loop(layout);

    // RUN ANIMATION
    bool done = false;

    while (!done) {
        done = true;

        for (int i = 0; i < (int)horses.size(); i++) {
            progress[i] += std::uniform_int_distribution<int>(1, horses[i].getSpeed())(rng);

            if (progress[i] < raceLength)
                done = false;
        }

        screen.PostEvent(Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}
