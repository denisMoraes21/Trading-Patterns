#pragma once
#include <libpq-fe.h>
#include <string>
#include <memory>
#include <mutex>
#include <stdexcept>


class Database {
    public:
        static Database& instance();
        PGconn* getConn();

    private:
        Database();
        ~Database();

        PGconn* conn;

        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;
};