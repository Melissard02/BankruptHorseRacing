
#ifndef BANKRUPT_DATABASE_H
#define BANKRUPT_DATABASE_H
#include <sqlite3.h>
#include <string>
#include <vector>
#include "GameSave.h"

class Database {
  public:
  explicit Database(const std::string& dbPath = "appdata.db");
  ~Database();

  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;

  bool openDatabase();
  void closeDatabase();
  bool initializeSchema();

  bool saveGame(const GameSave& data);
  bool loadGame(const std::string& playerName, GameSave& outData);

  std::vector<std::string> listSaves();

  bool userExists(const std::string& playerName);


private:
  std::string path;
  sqlite3 *db = nullptr;
};

#endif // BANKRUPT_DATABASE_H
