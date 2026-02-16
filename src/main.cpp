#include "Api.h"


std::shared_ptr<Api> apiPtr;

void signalHandler(int) {
    if (apiPtr) apiPtr->stop();
    std::cout << "\nAPI stopped safely." << std::endl;
    std::_Exit(0);
}

int main() {
    Pistache::Port port(9080);
    Pistache::Address addr(Pistache::Ipv4::any(), port);

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    apiPtr = std::make_shared<Api>(addr);
    apiPtr->init(1);

    try {
        std::cout << "API started!" << std::endl;
        apiPtr->start();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        apiPtr->stop();
    }
}