#include "api/Api.h"

int main() {
    Pistache::Port port(9080);
    Pistache::Address addr(Pistache::Ipv4::any(), port);

    Api api(addr);
    api.init();
    api.start();
}