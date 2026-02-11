#include "TuiMainMenu.h"

#include <ftxui/component/component.hpp>
// #include <ftxui/component/catch_event.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int TuiMainMenu::mainMenu() {
    int selected = 0;
    bool done = false;
    std::vector<std::string> options = {
        "Player Info",
        "Betting",
        "Horse",
        "Bank",
        "Start Race",
        "Save and Exit"
    };

    // THE INTERACTIVE MENU
    auto menu = Menu(&options, &selected);


    // CATCH ENTER ON THE MENU AND EXIT THE LOOP
    auto interactiveMenu = menu | CatchEvent([&](Event event) {
        if (event == Event::Return) {
            done = true;
            screen.Post(Event::Custom);
            return true;
        }
        return false;
    });

    // RENDERER THAT JUST DRAWS THE MENU
    auto layout = Renderer(interactiveMenu, [&] {
        if (done)
            screen.ExitLoopClosure()();
        return vbox({
            text("=== BANKRUPT RACING ===") | bold | center,
            separator(),
            menu->Render() | center
        });
    });

    // RUN THE UI LOOP
    screen.Loop(layout);
    return selected;
}
