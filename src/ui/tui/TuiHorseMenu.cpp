#include "TuiHorseMenu.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;

TuiHorseMenu::TuiHorseMenu(ScreenInteractive& screen,
                           std::vector<Horse>& horses)
    : screen(screen), horses(horses) {}

void TuiHorseMenu::horseMenu() {
    int selected = 0;

    std::vector<std::string> options = {
        "Show All Horses",
        "View Horse Stats",
        "Return to Main Menu"
    };

    auto menu = Menu(&options, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== HORSE MENU ===") | bold | center,
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);

    if (selected == 0) showHorseList();
    else if (selected == 1) showSingleHorsePrompt();
}

void TuiHorseMenu::showHorseList() {
    auto layout = Renderer([&] {
        std::vector<Element> list;

        for (auto& h : horses)
            list.push_back(text("• " + h.getName()));

        return vbox({
            text("=== ALL HORSES ===") | bold | center,
            separator(),
            vbox(list) | center,
            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}

void TuiHorseMenu::showSingleHorsePrompt() {
    int selected = 0;

    std::vector<std::string> names;
    for (auto& h : horses)
        names.push_back(h.getName());

    auto menu = Menu(&names, &selected);

    auto layout = Renderer(menu, [&] {
        return vbox({
            text("=== SELECT HORSE ===") | bold | center,
            separator(),
            menu->Render() | center
        });
    });

    screen.Loop(layout);

    showSingleHorse(selected);
}

void TuiHorseMenu::showSingleHorse(int index) {
    Horse& h = horses[index];

    auto layout = Renderer([&] {
        return vbox({
            text("=== HORSE STATS ===") | bold | center,
            separator(),
            text("Name: " + h.getName()),
            text("Speed: " + std::to_string(h.getSpeed())),
            text("Stamina: " + std::to_string(h.getStamina())),
            text("Luck: " + std::to_string(h.getLuck())),
            text("Popularity: " + std::to_string(h.getPopularity())),

            separator(),
            text("Press ESC to return") | dim | center
        });
    });

    screen.Loop(layout);
}
