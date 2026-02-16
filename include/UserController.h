#pragma once

#include <pistache/http.h>
#include <pistache/router.h>
#include "UserModel.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <string>

class UserController {
public:
    static void getUsers(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    static void addUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};
