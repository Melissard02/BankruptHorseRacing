#include "TuiRaceMenu.h"

#include "RaceAnimation.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

TuiRaceMenu::TuiRaceMenu(ScreenInteractive& screen,
                         Player& player,
                         std::vector<Horse>& horses,
                         std::vector<Better>& npcs,
                         bool legendarySpawned,
                         const std::string& legendaryName)
    : screen(screen), player(player), horses(horses),
      npcs(npcs), legendarySpawned(legendarySpawned),
      legendaryName(legendaryName) {}

void TuiRaceMenu::raceMenu() {
    auto layout = Renderer([&] {
        return vbox({
            text("=== RACE TIME ===") | bold | center,
            separator(),
            text("Press Enter to start the race"),
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);

    // START RACE ANIMATION
    RaceAnimation anim(screen, player, horses, npcs, legendarySpawned, legendaryName);
    anim.runRace();
}
