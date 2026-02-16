#pragma once

class Api {
    public:
        explicit Api(Pistache::Address addr);

        void init(size_t threads = 2);
        void start();

    private:
        void setupRoutes();
        void health(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response);

}