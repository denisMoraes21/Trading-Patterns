#include "UserModel.h"
#include <libpq-fe.h>
#include <stdexcept>

void UserModel::tableExists() {

    // Create connection
    PGconn* conn = Database::instance().getConn();
    
    // Query
    const char* createTableQuery = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id SERIAL PRIMARY KEY, "
        "name TEXT NOT NULL, "
        "age INTEGER"
        ");";

    // Execute query
    PGresult* res = PQexec(conn, createTableQuery);

    // Verify query result
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string err = PQerrorMessage(conn);

        // Clear buffer
        PQclear(res);

        throw std::runtime_error("Error during create table: " + err);
    }

    // Clear buffer
    PQclear(res);
}

std::vector<User> UserModel::getAllUsers() {
    tableExists();

    // Create connection
    PGconn* conn = Database::instance().getConn();

    // Query
    const char* getAllUsersQuery = 
        "SELECT * FROM users;";

    // Execute query
    PGresult* res = PQexec(conn, getAllUsersQuery);

    std::vector<User> users;
    
    // Return tuples
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; ++i) {
            users.push_back(User{
                std::stoi(PQgetvalue(res, i, 0)),
                PQgetvalue(res, i, 1)
            });
        }
    } else {

        // Clean buffer
        PQclear(res);
        throw std::runtime_error("Erro na query: " + std::string(PQerrorMessage(conn)));
    }

    // Clean buffer
    PQclear(res);
    return users;
}

int UserModel::addUser(const char* name, const int age) {

    // Create connection
    PGconn* conn = Database::instance().getConn();

    // Warning: SQL injection: params order and special characters 
    //into params.

    // std::string addUserQuery = 
    //     "INSERT INTO users (name, age) VALUES ('"
    //     + std::string(name) + "', "
    //     + std::to_string(age) + ");";

    // PGresult* res = PQexec(conn, addUserQuery.c_str());

    const char* paramValues[2];
    paramValues[0] = name;
    std::string ageStr = std::to_string(age);
    paramValues[1] = ageStr.c_str();

    PGresult* res = PQexecParams(
        conn,
        "INSERT INTO users (name, age) VALUES ($1, $2);",
        2,
        nullptr,
        paramValues,
        nullptr,
        nullptr,
        0
    );
    

    // Return tuples
    if (PQresultStatus(res) == PGRES_COMMAND_OK) {
        PQclear(res);
        return 1;
    }

    PQclear(res);
    throw std::runtime_error("Erro na query: " + std::string(PQerrorMessage(conn)));
}
