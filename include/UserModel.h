#pragma once
#include "Database.h"
#include <vector>
#include <string>

struct User {
    int id;
    std::string name;
};

class UserModel {
public:
    static void tableExists();
    static std::vector<User> getAllUsers();
    static int addUser(const char* name, const int age);
};
