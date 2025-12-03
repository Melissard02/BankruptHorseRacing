#include "RaceAnimation.h"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>

using namespace ftxui;

// -----------------------------------------------------------
// Run entire race sequence
// -----------------------------------------------------------

void RaceAnimation::runRace() {
    auto screen = ScreenInteractive::Fullscreen();

    // COUNTDOWN
    runCountdown();

    // Simulate race and gather standings
    std::vector<int> placements(horses.size());
    simulateRace(placements);

    // Show winner & payout info
    showWinnerScreen(placements);
}

// -----------------------------------------------------------
// Countdown (3..2..1..GO!)
// -----------------------------------------------------------

void RaceAnimation::runCountdown() {
    auto screen = ScreenInteractive::Fullscreen();

    int tick = 3;

    auto layout = Renderer([&] {
        return vbox({
            text("=== RACE STARTING ===") | bold | center,
            separator(),
            text(std::to_string(tick)) | bold | center,
            separator(),
            text("Get ready!") | dim | center
        });
    });

    while (tick > 0) {
        screen.Loop(layout);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        tick--;
    }

    // Show GO!
    auto goLayout = Renderer([&] {
        return vbox({
            text("=== RACE STARTING ===") | bold | center,
            separator(),
            text("GO!") | bold | color(Color::Green) | center,
            separator(),
            text("The horses are off!") | dim | center
        });
    });

    screen.Loop(goLayout);
    std::this_thread::sleep_for(std::chrono::milliseconds(700));
}

// -----------------------------------------------------------
// Simulate race progress
// -----------------------------------------------------------

void RaceAnimation::simulateRace(std::vector<int>& placements) {
    auto screen = ScreenInteractive::Fullscreen();

    std::vector<int> progress(horses.size(), 0);
    std::vector<bool> finished(horses.size(), false);
    int finishedCount = 0;

    std::mt19937 rng(std::random_device{}());

    auto layout = Renderer([&] {
        std::vector<Element> lines;

        for (int i = 0; i < (int)horses.size(); i++) {
            int barWidth = progress[i] * 50 / raceLength;
            if (barWidth > 50) barWidth = 50;

            std::string bar(barWidth, '=');
            bar += ">";

            lines.push_back(
                hbox({
                    text(horses[i].getName() + " ") | bold,
                    text(bar),
                })
            );
        }

        return vbox({
            text("=== RACE IN PROGRESS ===") | bold | center,
            separator(),
            vbox(lines),
            separator(),
            text("Press Q to skip") | dim | center
        });
    });

    // Race loop
    screen.Loop(layout);

    while (finishedCount < (int)horses.size()) {
        for (int i = 0; i < (int)horses.size(); i++) {
            if (finished[i]) continue;

            // Race tick logic — matches your Race.cpp
            std::uniform_int_distribution<int> dist(1, horses[i].getSpeed());
            int step = dist(rng);

            // Legendary buff
            if (horses[i].isLegendary())
                step += 3;

            progress[i] += step;

            if (progress[i] >= raceLength) {
                finished[i] = true;
                placements[finishedCount++] = i;
            }
        }

        screen.PostEvent(Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

// -----------------------------------------------------------
// Winner screen & payout
// -----------------------------------------------------------

void RaceAnimation::showWinnerScreen(const std::vector<int>& placements) {
    auto screen = ScreenInteractive::Fullscreen();

    int winnerIndex = placements[0];
    Horse& winner = horses[winnerIndex];

    auto layout = Renderer([&] {
        return vbox({
            text("=== RACE RESULTS ===") | bold | center,
            separator(),
            text("WINNER: " + winner.getName()) | bold | color(Color::Green) | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}
