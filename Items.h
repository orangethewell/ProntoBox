#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "db.h"

extern Migration TransactionMigrations[];

inline std::string timestampToISO(std::time_t t) {
    std::tm* tm_ptr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::setw(4) << (tm_ptr->tm_year + 1900) << "-"
        << std::setw(2) << std::setfill('0') << (tm_ptr->tm_mon + 1) << "-"
        << std::setw(2) << std::setfill('0') << tm_ptr->tm_mday << " "
        << std::setw(2) << std::setfill('0') << tm_ptr->tm_hour << ":"
        << std::setw(2) << std::setfill('0') << tm_ptr->tm_min << ":"
        << std::setw(2) << std::setfill('0') << tm_ptr->tm_sec;
    return oss.str();
}

inline std::time_t ISOToTimestamp(const std::string& iso) {
    std::tm tm = {};
    std::istringstream ss(iso);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        std::cerr << "Falha ao converter ISO para timestamp!" << std::endl;
        return 0;
    }
    return std::mktime(&tm); // retorna std::time_t
}


struct TransactionItem {
    int id;
    float value;
    std::string description;
    std::time_t date;

    static void db_initTransactionTable(sqlite3* db);
    static std::vector<TransactionItem> db_getAll(sqlite3* db);
    static bool db_insert(sqlite3* db, const TransactionItem& item);
    static bool db_update(sqlite3* db, const TransactionItem& item);
    static bool db_delete(sqlite3* db, int tID);
    static bool db_get(sqlite3* db, int tID, TransactionItem& outItem);
};

enum class ClientStatus {
    Active,
    Inactive,
    Potential,
    Blocked
};

struct ClientItem {
    int id;
    std::string type;              // "Pessoa Física" ou "Empresa"
    std::string name;              // Nome completo ou Razão social
    std::string nickname;          // Apelido ou nome fantasia
    std::string document;          // CPF ou CNPJ
    std::string contactNumber;     // Telefone/WhatsApp principal
    std::string email;             // E-mail de contato
    std::string address;           // Rua/Avenida
    std::string addressNum;        // Número
    std::string neighborhood;      // Bairro
    std::string city;              // Cidade
    std::string state;             // Estado (sigla)
    std::string zipCode;           // CEP
    std::string notes;             // Observações gerais
    ClientStatus status;
    time_t createdAt;
    time_t updatedAt;

    static void db_initClientTable(sqlite3* db);
    static std::vector<ClientItem> db_getAll(sqlite3* db);
    static bool db_insert(sqlite3* db, const ClientItem& item);
    static bool db_update(sqlite3* db, const ClientItem& item);
    static bool db_delete(sqlite3* db, int tID);
    static bool db_get(sqlite3* db, int tID, ClientItem& outItem);
};

#endif // ITEMS_H_INCLUDED
