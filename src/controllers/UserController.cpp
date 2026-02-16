#include "UserController.h"

void UserController::getUsers(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response) {
    auto users = UserModel::getAllUsers();
    std::string result = "[";

    for (size_t i = 0; i < users.size(); ++i) {
        result += "{\"id\":" + std::to_string(users[i].id) + 
                  ",\"name\":\"" + users[i].name + "\"}";
        if (i != users.size() - 1) result += ",";
    }

    result += "]";
    response.send(Pistache::Http::Code::Ok, result);
}

void UserController::addUser(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    
    std::string body = request.body();

    // Json parser
    rapidjson::Document doc;
    if (doc.Parse(body.c_str()).HasParseError()) {
        std::string err = std::string("Erro ao parsear JSON: ") + rapidjson::GetParseError_En(doc.GetParseError());
        response.send(Pistache::Http::Code::Bad_Request, err);
        return;
    }

    // Verifica se os campos existem
    if (!doc.HasMember("name") || !doc["name"].IsString() ||
        !doc.HasMember("age") || !doc["age"].IsInt()) {
        response.send(Pistache::Http::Code::Bad_Request, "Campos 'name' e 'age' são obrigatórios");
        return;
    }

    std::string name = doc["name"].GetString();
    int age = doc["age"].GetInt();

    try {
        // Adiciona no banco
        UserModel::addUser(name.c_str(), age);
    } catch (const std::exception& e) {
        response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
        return;
    }

    // Retorna sucesso
    response.send(Pistache::Http::Code::Created, "Usuário adicionado com sucesso!");
}
