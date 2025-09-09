#include "Items.h"
#include <wx/wx.h>

Migration TransactionMigrations[] = {
    { "Transactions", 1,
        "CREATE TABLE IF NOT EXISTS Transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "value REAL NOT NULL, "
        "description TEXT, "
        "date VARCHAR(30) NOT NULL);" }
};

Migration ClientMigrations[] = {
    { "Clients", 1,
        "CREATE TABLE IF NOT EXISTS Clients ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "type VARCHAR(20) NOT NULL, "
        "name VARCHAR(150) NOT NULL, "
        "nickname VARCHAR(100), "
        "document VARCHAR(20), "
        "contactNumber VARCHAR(20) NOT NULL, "
        "email VARCHAR(255), "
        "address VARCHAR(150), "
        "addressNum VARCHAR(10), "
        "neighboorhood VARCHAR(100), "
        "city VARCHAR(100), "
        "state CHAR(2), "
        "zipCode CHAR(9), "
        "notes TEXT, "
        "status INTEGER NOT NULL DEFAULT 1, "
        "createdAt VARCHAR(30) NOT NULL, "
        "updatedAt VARCHAR(30) NOT NULL);"}
};

void TransactionItem::db_initTransactionTable(sqlite3* db)
{
    int TransactionTableVersion = db_getTableVersion(db, "Transactions");
    int i = (sizeof(TransactionMigrations) / sizeof(TransactionMigrations[0])) - 1;
    int TransactionMigrationVersion = TransactionMigrations[i].version;

    for (const auto& migration : TransactionMigrations) {
        if (migration.version > TransactionTableVersion) {
            char* errMsg = nullptr;

            if (sqlite3_exec(db, migration.sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
                wxMessageBox(wxString::FromUTF8(errMsg), "Migration Error", wxICON_ERROR | wxOK);
                sqlite3_free(errMsg);
                break;
            }
            std::string updateVersion = "INSERT OR REPLACE INTO table_versions (table_name, version) VALUES ('Transactions', " + std::to_string(TransactionMigrationVersion) + ");";
            sqlite3_exec(db, updateVersion.c_str(), nullptr, nullptr, nullptr);
        }
    }
}

void ClientItem::db_initClientTable(sqlite3* db)
{
    int ClientTableVersion = db_getTableVersion(db, "Clients");
    int i = (sizeof(ClientMigrations) / sizeof(ClientMigrations[0])) - 1;
    int ClientMigrationVersion = ClientMigrations[i].version;

    for (const auto& migration: ClientMigrations) {
        if (migration.version > ClientTableVersion) {
            char* errMsg = nullptr;

            if (sqlite3_exec(db, migration.sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
                wxMessageBox(wxString::FromUTF8(errMsg), "Migration Error", wxICON_ERROR | wxOK);
                sqlite3_free(errMsg);
                break;
            }

            std::string updateVersion = "INSERT OR REPLACE INTO table_versions (table_name, version) VALUES ('Clients', " + std::to_string(ClientMigrationVersion) + ");";
            sqlite3_exec(db, updateVersion.c_str(), nullptr, nullptr, nullptr);
        }
    }
}

std::vector<TransactionItem> TransactionItem::db_getAll(sqlite3* db)
{
    std::vector<TransactionItem> result;

    const char* sql = "SELECT id, value, description, date FROM Transactions ORDER BY id ASC;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        wxMessageBox(sqlite3_errmsg(db), "Database Error", wxICON_ERROR | wxOK);
        return result;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        TransactionItem t;
        t.id = sqlite3_column_int(stmt, 0);
        t.value = static_cast<float>(sqlite3_column_double(stmt, 1));
        t.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        t.date = ISOToTimestamp(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))));

        result.push_back(t);
    }

    sqlite3_finalize(stmt);
    return result;
}

std::vector<ClientItem> ClientItem::db_getAll(sqlite3* db)
{
    std::vector<ClientItem> result;

    const char* sql = "SELECT id, type, name, nickname, document, contactNumber, email, address, addressNum, neighborhood, city, state, zipCode, notes, status, createdAt, updatedAt FROM Clients ORDER BY id ASC;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        wxMessageBox(sqlite3_errmsg(db), "Database Error", wxICON_ERROR | wxOK);
        return result;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ClientItem t;
        t.id = sqlite3_column_int(stmt, 0);
        t.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        t.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        t.nickname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        t.document = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        t.contactNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        t.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        t.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        t.addressNum = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        t.neighborhood = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        t.city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        t.state = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
        t.zipCode = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12));
        t.notes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 13));
        t.status = sqlite3_column_int(stmt, 14);
        t.createdAt = ISOToTimestamp(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 15))));
        t.updatedAt = ISOToTimestamp(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16))));

        result.push_back(t);
    }

    sqlite3_finalize(stmt);
    return result;
}

bool TransactionItem::db_insert(sqlite3* db, const TransactionItem& item)
{
    const char* sql = "INSERT INTO Transactions (value, description, date) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        wxMessageBox(sqlite3_errmsg(db), "Database Error", wxICON_ERROR | wxOK);
        return false;
    }

    // value -> REAL
    sqlite3_bind_double(stmt, 1, static_cast<double>(item.value));

    // description -> TEXT
    sqlite3_bind_text(stmt, 2, item.description.c_str(), -1, SQLITE_TRANSIENT);

    // date -> TEXT (ISO 8601)
    sqlite3_bind_text(stmt, 3, timestampToISO(item.date).c_str(), -1, SQLITE_TRANSIENT);

    bool success = true;
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        wxMessageBox(sqlite3_errmsg(db), "Insert Error", wxICON_ERROR | wxOK);
        success = false;
    }

    sqlite3_finalize(stmt);
    return success;
}

bool TransactionItem::db_update(sqlite3* db, const TransactionItem& item)
{
    const char* sql = "UPDATE Transactions SET value = ?, description = ?, date = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        wxMessageBox(sqlite3_errmsg(db), "Database Error", wxICON_ERROR | wxOK);
        return false;
    }

    // value -> REAL
    sqlite3_bind_double(stmt, 1, static_cast<double>(item.value));

    // description -> TEXT
    sqlite3_bind_text(stmt, 2, item.description.c_str(), -1, SQLITE_TRANSIENT);

    // date -> TEXT (ISO 8601)
    sqlite3_bind_text(stmt, 3, timestampToISO(item.date).c_str(), -1, SQLITE_TRANSIENT);

    // id -> INTEGER
    sqlite3_bind_int(stmt, 4, item.id);

    bool success = true;
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        wxMessageBox(sqlite3_errmsg(db), "Update Error", wxICON_ERROR | wxOK);
        success = false;
    }

    sqlite3_finalize(stmt);
    return success;
}

bool TransactionItem::db_delete(sqlite3* db, int tID)
{
    if (!db) return false;

    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM transactions WHERE id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        wxMessageBox(wxString::Format("Erro ao preparar DELETE: %s", sqlite3_errmsg(db)),
                     "Erro", wxOK | wxICON_ERROR);
        return false;
    }

    if (sqlite3_bind_int(stmt, 1, tID) != SQLITE_OK)
    {
        wxMessageBox(wxString::Format("Erro ao vincular ID: %s", sqlite3_errmsg(db)),
                     "Erro", wxOK | wxICON_ERROR);
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        wxMessageBox(wxString::Format("Erro ao executar DELETE: %s", sqlite3_errmsg(db)),
                     "Erro", wxOK | wxICON_ERROR);
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool TransactionItem::db_get(sqlite3* db, int tID, TransactionItem& outItem)
{
    if (!db) return false;

    const char* sql = "SELECT id, value, description, date FROM Transactions WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        wxMessageBox(wxString::Format("Erro ao preparar SELECT: %s", sqlite3_errmsg(db)),
                     "Erro", wxOK | wxICON_ERROR);
        return false;
    }

    if (sqlite3_bind_int(stmt, 1, tID) != SQLITE_OK)
    {
        wxMessageBox(wxString::Format("Erro ao vincular ID: %s", sqlite3_errmsg(db)),
                     "Erro", wxOK | wxICON_ERROR);
        sqlite3_finalize(stmt);
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        outItem.id = sqlite3_column_int(stmt, 0);
        outItem.value = static_cast<float>(sqlite3_column_double(stmt, 1));
        outItem.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        outItem.date = ISOToTimestamp(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))));
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}

