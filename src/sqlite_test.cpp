#include <iostream>
#include <sqlite3.h>

int main() {
  sqlite3* db = nullptr;

  int rc = sqlite3_open("appdata.db", &db);
  if (rc != SQLITE_OK) {
    std::cerr << "Open DB failed: " << sqlite3_errmsg(db) << "\n";
    return 1;
  }

  std::cout << "DB opened successfully!\n";

  const char* createSql =
      "CREATE TABLE IF NOT EXISTS users ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "username TEXT NOT NULL,"
      "highscore INTEGER NOT NULL DEFAULT 0"
      ");";

  char* errMsg = nullptr;
  rc = sqlite3_exec(db, createSql, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Create table failed: " << (errMsg ? errMsg : "unknown") << "\n";
    sqlite3_free(errMsg);
    sqlite3_close(db);
    return 1;
  }

  std::cout << "Table check/create succeeded!\n";

  sqlite3_close(db);
  std::cout << "DB closed. Done.\n";
  return 0;
}

