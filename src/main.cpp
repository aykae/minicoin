#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include "blockchain.h"
#include <iostream>
#include <fmt/core.h>
#include <mutex>

// #define USING_SERVER

int difficulty = 5;
std::mutex blockMutex;

int mine(Block* block) {
    block->increment_nonce();
    std::string hash = block->compute_hash();
    return hash.substr(hash.length()-difficulty, difficulty) == std::string(difficulty, '0');
}

void setup_server(httplib::Server& svr, Block* block) {
    svr.Get("/mine", [&](const httplib::Request &, httplib::Response &res) {
        res.set_content(fmt::format("{{\"message\": \"{}\" }}", block->compute_hash()), "application/json");
    });

    svr.listen("localhost", 8080);
}


int main() {

    #ifdef USING_SERVER
    httplib::Server svr;
    std::thread server_thread([&] {
        setup_server(svr, genesis);
    });
    server_thread.detach();
    #endif

    Blockchain blockchain;
    std::cout << "Blockchain generated." << std::endl;

    while (1) {
        Block* block = blockchain.create_block();

        while(!mine(block)) {continue;}
        std::cout << "Block Number " << blockchain.get_length()-1 << ": " << blockchain.get_prev_hash() << std::endl;
    }



    #ifdef USING_SERVER
    while (1) {}
    #else
    #endif



    return 0;
}