#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>

class Api {
public:
    explicit Api(Pistache::Address addr);

    void init(size_t threads = 2);
    void start();
    void stop();

private:
    void setupRoutes();

    void health(const Pistache::Rest::Request&, 
                Pistache::Http::ResponseWriter response);

    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
};
