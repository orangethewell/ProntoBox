#include "db.h"
#include <iostream>
#include <wx/msgdlg.h>

#include "Items.h"

sqlite3* g_db = nullptr;

bool db_open(const char* path)
{
    int rc = sqlite3_open(path, &g_db);
    // wxMessageBox("Inicializando SQLite3...", "Banco de dados");
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao abrir DB: " << sqlite3_errmsg(g_db) << "\n";
        sqlite3_close(g_db);
        g_db = nullptr;
        return false;
    }
    // exemplo: modo WAL
    sqlite3_exec(g_db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, nullptr);
    db_initialize();
    return true;
}

int db_getTableVersion(sqlite3* db, const std::string& tableName) {
    sqlite3_stmt* stmt;
    int version = 0;
    std::string sql = "SELECT version FROM table_versions WHERE table_name='" + tableName + "';";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            version = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return version;
}

void db_initialize()
{
    std::string TableVersionningSys = "CREATE TABLE IF NOT EXISTS table_versions (table_name TEXT PRIMARY KEY, version INTEGER NOT NULL);";
    sqlite3_exec(g_db, TableVersionningSys.c_str(), nullptr, nullptr, nullptr);
    TransactionItem::db_initTransactionTable(g_db);
    ClientItem::db_initClientTable(g_db);
}

void db_close()
{
    if (g_db) {
        sqlite3_close(g_db);
        g_db = nullptr;
    }
}
