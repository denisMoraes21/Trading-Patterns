#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Pistache;

class Api {

public:
    explicit Api(Address addr) 
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr)){}

    void init(size_t threads = 2) {
        auto opts = Http::Endpoint::options().threads(threads);
        httpEndpoint->init(opts);
        setupRoutes();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }
    
private:
    void setupRoutes() {
        using namespace Rest;

        Routes::Get(router, "/", Routes::bind(&Api::hello, this));
        Routes::Get(router, "/hello/:name", Routes::bind(&Api::helloName, this));
    }

    void hello(const Rest::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "API funcionando!");
    }

    void helloName(const Rest::Request& request, Http::ResponseWriter response) {
        auto name = request.param(":name").as<std::string>();
        response.send(Http::Code::Ok, "Hello " + name);
    }

    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
};

int main() {
    Port port(18080);
    Address addr(Ipv4::any(), port);

    Api api(addr);
    api.init(2);
    api.start();
}