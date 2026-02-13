//
// Created by melis on 2/11/2026.
//

#include "LoadScreen.h"
#include "Database.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

// ---------------------- Utility ----------------------
void LoadScreen::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// ------------------- LOAD SCREEN -------------------
int LoadScreen::loadScreen() {
  clearScreen();
  std::cout << "================================\n";
  std::cout << "BANKRUPT HORSE RACING\n";
  std::cout << "================================\n";

  std::cout << "1. New Game\n";
  std::cout << "2. Load Game\n";
  std::cout << "3. Settings\n";
  std::cout << "0. Exit\n";

  std::cout << "\n> ";
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

// ------------------- NEW GAME -------------------
std::string LoadScreen::newGame() {
  clearScreen();
  std::cout << "==============================\n";
  std::cout << "NEW GAME\n";
  std::cout << "==============================\n";

  std::string name;

  while (true) {
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    if (name.empty()) {
      std::cout << "Name can't be empty.\n";
      continue;
    }

    if (database.userExists(name)) {
      std::string overwrite;
      std::cout << "That name is already in use!\n";
      std::cout << "Overwrite it? (y/n): ";
      std::getline(std::cin, overwrite);

      if (overwrite == "y" || overwrite == "Y") {
        // optional: database.deleteSave(name);
        break; // accept this name
      }

      std::cout << "Okay—pick a different name.\n";
      continue; // go back and ask again
    }

    // name does not exist
    break;
  }

  return name;

}

// ------------------- LOAD GAME -------------------
bool LoadScreen::loadGame() {
  clearScreen();
  std::cout << "==============================\n";
  std::cout << "Saves\n";
  std::cout << "==============================\n";

  auto saves = database.listSaves();
  if (saves.empty()) {
    std::cout << "No saves found!\n";
    return false;
  }

  for (int i = 0; i < static_cast<int>(saves.size()); i++) {
    std::cout << (i + 1) << ". " << saves[i] << "\n";
  }
  std::cout << "0. Back\n";

  std::cout << "> ";
  int choice{};
  std::cin >> choice;

  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return false;
  }

  if (choice == 0) return false;

  int index = choice - 1;
  if (index < 0 || index >= static_cast<int>(saves.size())) {
    std::cout << "Invalid choice.\n";
    return false;
  }

  if (!database.loadGame(saves[index], gsave)) {
    std::cout << "Failed to load save.\n";
    return false;
  }

  return true;
}


// void LoadScreen::settings() {
//   clearScreen();
//   std::cout << "=============================\n";
//   std::cout << "SETTINGS\n";
//   std::cout << "=============================\n";
// }