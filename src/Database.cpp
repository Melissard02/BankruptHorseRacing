//
// Created by melis on 2/11/2026.
//

#include "Database.h"
#include <iostream>
#include <vector>

Database::Database(const std::string &dbPath) : path(dbPath) {}

Database::~Database() {
  closeDatabase();
}

bool Database::openDatabase() {
  if (db) return true;

  if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
    db = nullptr;
    return false;
  }
  return true;
}

void Database::closeDatabase() {
  if (db) {
    sqlite3_close(db);
    db = nullptr;
  }
}

bool Database::initializeSchema() {
  if (!openDatabase()) return false;

  const char* sql =
    "CREATE TABLE IF NOT EXISTS players("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "name TEXT NOT NULL UNIQUE,"
    "balance INTEGER NOT NULL,"
    "income INTEGER NOT NULL,"
    "bets INTEGER NOT NULL DEFAULT 0,"
    "betAmount INTEGER NOT NULL DEFAULT 0,"
    "betHorseIndex INTEGER NOT NULL DEFAULT -1"
    ");"
    "CREATE TABLE IF NOT EXISTS horses("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "player_id INTEGER NOT NULL,"
    "name TEXT NOT NULL,"
    "legendary INTEGER NOT NULL,"
    "speed INTEGER NOT NULL,"
    "stamina INTEGER NOT NULL,"
    "popularity INTEGER NOT NULL,"
    "luck INTEGER NOT NULL,"
    "wins INTEGER NOT NULL,"
    "races INTEGER NOT NULL,"
    "FOREIGN KEY (player_id) REFERENCES players(id)"
    ");";

  char* err = nullptr;
  if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
    std::cerr << "Error when creating database: " << (err ? err : "unknown") << "\n";
    sqlite3_free(err);
    return false;
  }
  return true;
}

bool Database::saveGame(const GameSave &data) {
  if (!initializeSchema()) return false;

  const char* upsertPlayer =
    "INSERT INTO players (name, balance, income, bets, betAmount, betHorseIndex)"
    "VALUES (?, ?, ?, ?, ?, ?)"
    "ON CONFLICT(name) DO UPDATE SET "
    "balance=excluded.balance, income=excluded.income, bets=excluded.bets,"
    "betAmount=excluded.betAmount, betHorseIndex=excluded.betHorseIndex;";

  sqlite3_stmt* stmt = nullptr;
  if (sqlite3_prepare_v2(db, upsertPlayer, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare upsertPlayer failed: " << sqlite3_errmsg(db) << "\n";
    return false;
  }

  sqlite3_bind_text(stmt, 1, data.playerName.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, data.balance);
  sqlite3_bind_int(stmt, 3, data.income);
  sqlite3_bind_int(stmt, 4, data.bets);
  sqlite3_bind_int(stmt, 5, data.betAmount);
  sqlite3_bind_int(stmt, 6, data.betHorseIndex);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Insert player failed: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }
  sqlite3_finalize(stmt);

  const char* getId = "SELECT id FROM players WHERE name = ?;";
  if (sqlite3_prepare_v2(db, getId, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare getId failed: " << sqlite3_errmsg(db) << "\n";
    return false;
  }
  sqlite3_bind_text(stmt, 1, data.playerName.c_str(), -1, SQLITE_TRANSIENT);

  int rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW) {
    std::cerr << "Player id not found.\n";
    sqlite3_finalize(stmt);
    return false;
  }
  int playerId = sqlite3_column_int(stmt, 0);
  sqlite3_finalize(stmt);

  const char* delHorses = "DELETE FROM horses WHERE player_id = ?;";
  if (sqlite3_prepare_v2(db, delHorses, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare delHorses failed: " << sqlite3_errmsg(db) << "\n";
    return false;
  }
  sqlite3_bind_int(stmt, 1, playerId);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Delete horses failed: " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }
  sqlite3_finalize(stmt);

  const char* insHorse =
        "INSERT INTO horses (player_id, name, legendary, speed, stamina, popularity, luck, wins, races) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

  if (sqlite3_prepare_v2(db, insHorse, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare insHorse failed: " << sqlite3_errmsg(db) << "\n";
    return false;
  }

  for (const auto& h : data.horses) {
    sqlite3_bind_int(stmt, 1, playerId);
    sqlite3_bind_text(stmt, 2, h.horseName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, h.legendary ? 1 : 0);
    sqlite3_bind_int(stmt, 4, h.speed);
    sqlite3_bind_int(stmt, 5, h.stamina);
    sqlite3_bind_int(stmt, 6, h.popularity);
    sqlite3_bind_int(stmt, 7, h.luck);
    sqlite3_bind_int(stmt, 8, h.wins);
    sqlite3_bind_int(stmt, 9, h.races);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cerr << "Insert horse failed: " << sqlite3_errmsg(db) << "\n";
      sqlite3_finalize(stmt);
      return false;
    }
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
  }

  sqlite3_finalize(stmt);
  return true;
}

bool Database::loadGame(const std::string& playerName, GameSave& outData) {
    if (!initializeSchema()) return false;

    outData = GameSave{};
    outData.playerName = playerName;

    const char* selPlayer =
        "SELECT id, balance, income, bets, betAmount, betHorseIndex "
        "FROM players WHERE name = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, selPlayer, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare selPlayer failed: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, playerName.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    int playerId = sqlite3_column_int(stmt, 0);
    outData.balance = sqlite3_column_int(stmt, 1);
    outData.income = sqlite3_column_int(stmt, 2);
    outData.bets = sqlite3_column_int(stmt, 3);
    outData.betAmount = sqlite3_column_int(stmt, 4);
    outData.betHorseIndex = sqlite3_column_int(stmt, 5);
    sqlite3_finalize(stmt);


    const char* selHorses =
        "SELECT name, legendary, speed, stamina, popularity, luck, wins, races "
        "FROM horses WHERE player_id = ?;";

    if (sqlite3_prepare_v2(db, selHorses, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare selHorses failed: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, playerId);

    outData.horses.clear();
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        HorseSave h;
        h.horseName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        h.legendary = sqlite3_column_int(stmt, 1) != 0;
        h.speed = sqlite3_column_int(stmt, 2);
        h.stamina = sqlite3_column_int(stmt, 3);
        h.popularity = sqlite3_column_int(stmt, 4);
        h.luck = sqlite3_column_int(stmt, 5);
        h.wins = sqlite3_column_int(stmt, 6);
        h.races = sqlite3_column_int(stmt, 7);

        outData.horses.push_back(h);
    }

    sqlite3_finalize(stmt);
    return true;
}

std::vector<std::string> Database::listSaves() {
  std::vector<std::string> saves;

  if (!initializeSchema()) return saves;

  const char* sql = "SELECT name FROM players ORDER BY id DESC;";
  sqlite3_stmt* stmt = nullptr;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare saves failed: " << sqlite3_errmsg(db) << "\n";
    return saves;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    const unsigned char* text = sqlite3_column_text(stmt, 0);
    if (text) saves.emplace_back(reinterpret_cast<const char*>(text));
  }

  sqlite3_finalize(stmt);
  return saves;
}

bool Database::userExists(const std::string &playerName) {
  if (!initializeSchema()) return false;

  const char* sql = "SELECT 1 FROM players WHERE name = ? LIMIT 1;";
  sqlite3_stmt* stmt = nullptr;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare userExists failed: " << sqlite3_errmsg(db) << "\n";
    return false;
  }

  sqlite3_bind_text(stmt, 1, playerName.c_str(), -1, SQLITE_TRANSIENT);

  int rc = sqlite3_step(stmt);
  bool exists = (rc == SQLITE_ROW);

  sqlite3_finalize(stmt);
  return exists;
}

