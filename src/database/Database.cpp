#include "Database.h"
#include <iostream>

Database& Database::instance() {
    static Database db;
    return db;
}

PGconn* Database::getConn() {
    return conn;
}

Database::Database() {
    const char* conninfo = "host=localhost port=5433 dbname=trading_patterns user=denis password=1234";
    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        throw std::runtime_error(PQerrorMessage(conn));
    }
    std::cout << "Conexão com PostgreSQL estabelecida!" << std::endl;
}

Database::~Database() {
    if (conn) {
        PQfinish(conn);
        std::cout << "Conexão com PostgreSQL encerrada." << std::endl;
    }
}
