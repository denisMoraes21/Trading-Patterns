#include "Api.h"
#include "UserController.h"

using namespace Pistache;

Api::Api(Address addr)
    : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr)) {}

void Api::init(size_t threads) {
    auto opts = Pistache::Http::Endpoint::options()
                    .threads(threads)
                    .flags(Pistache::Tcp::Options::ReuseAddr);
    httpEndpoint->init(opts);
    setupRoutes();
}

void Api::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void Api::setupRoutes() {
    Rest::Routes::Get(router, "/health",
        Rest::Routes::bind(&Api::health, this));

    Rest::Routes::Get(router, "/users", 
        Rest::Routes::bind(&UserController::getUsers));

    Rest::Routes::Post(router, "/users",
        Rest::Routes::bind(&UserController::addUser));
}

void Api::health(const Rest::Request&, 
                 Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "API is running");
}

void Api::stop() {
    if (httpEndpoint)
        httpEndpoint->shutdown();
}

