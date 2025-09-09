#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED
#include "external\sqlite3.h"
#include <string>

extern sqlite3* g_db;

struct Migration {
    std::string tableName;
    int version;
    const char* sql;
};

bool db_open(const char* path);
int db_getTableVersion(sqlite3* db, const std::string& tableName);
void db_initialize();
void db_close();



#endif // DB_H_INCLUDED
