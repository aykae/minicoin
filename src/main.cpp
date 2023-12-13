#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include "block.h"
#include <iostream>
#include <fmt/core.h>
#include <mutex>

#define USING_SERVER

int difficulty = 10;
std::mutex blockMutex;

int mine(Block& block) {
    block.increment_nonce();
    std::string hash = block.hash();
    return hash.substr(hash.length()-difficulty, 2) == std::string(difficulty, '0');
}

void setup_server(httplib::Server& svr, Block& block) {
    svr.Get("/mine", [&](const httplib::Request &, httplib::Response &res) {
        res.set_content(fmt::format("{{\"message\": \"{}\" }}", block.hash()), "application/json");
    });

    svr.listen("localhost", 8080);
}


int main() {

    Block genesis;

    #ifdef USING_SERVER
    httplib::Server svr;
    std::thread server_thread([&] {
        setup_server(svr, genesis);
    });
    #endif
    
    Block b1;
    b1.id = 1;
    b1.prev_block = &genesis;

    std::cout << b1.id << std::endl;

    while (!mine(genesis))  {}
    b1.prev_hash = genesis.hash();

    #ifdef USING_SERVER
    std::string hash = genesis.hash();
    #else

    std::cout << b1.prev_hash << std::endl;
    std::cout << std::string(difficulty, '0') << std::endl;
    #endif

    return 0;
}