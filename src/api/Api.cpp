#include "Api.h"

using namespace Pistache;

Api::Api(Address addr)
    : httpEndpoint(std::make_shared<Http::Endpoint>(addr)) {}

void Api::init(size_t threads) {
    auto opts = Http::Endpoint::options().threads(threads);
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
}

void Api::health(const Rest::Request&, 
                 Http::ResponseWriter response) {
    response.send(Http::Code::Ok, "API is running");
}
