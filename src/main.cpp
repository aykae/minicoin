#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include "blockchain.h"
#include <iostream>
#include <fmt/core.h>
#include <mutex>

#define USING_SERVER

int difficulty = 5;
std::mutex blockMutex;

int mine(Block* block) {
    // std::cout << "In thread." << std::endl;
    block->increment_nonce();
    std::string hash = block->compute_hash();
    return hash.substr(hash.length()-difficulty, difficulty) == std::string(difficulty, '0');
}

// void setup_server(httplib::Server& svr, Blockchain* blockchain) {
//     svr.Get("/mine", [&](const httplib::Request &, httplib::Response &res) {
//         res.set_content(fmt::format("{{\"hash\": \"{}\", \"blen\": \"{}\", \"timestamp\": \"{}\"}}", blockchain->get_prev_hash(), blockchain->get_length()), "application/json");
//     });

//     svr.listen("localhost", 8080);
// }

void create_block_endpoint(httplib::Server& svr, Block* block) {
    svr.Get("/mine", [&](const httplib::Request &, httplib::Response &res) { 
        res.set_content(fmt::format("{{\"hash\": \"{}\", \"timestamp\": \"{}\"}}", block->compute_hash(), block->get_timestamp()), "application/json");
    });

    svr.listen("localhost", 8080);
}


int main() {

    Blockchain blockchain;

    #ifdef USING_SERVER
    httplib::Server svr;
    #else
    std::cout << "Blockchain generated." << std::endl;
    #endif

    while (1) {
        Block* block = blockchain.create_block();

        #ifdef USING_SERVER

        create_block_endpoint(svr, block);
        std::thread server_thread([&] {
            while(!mine(block)) {continue;}
            blockchain.add_block(block);
        });
        server_thread.join();
        std::cout << "Added new block." << std::endl;

        #else

        while(!mine(block)) {continue;}
        blockchain.add_block(block);
        std::cout << "Block Number " << blockchain.get_length()-1 << ": " << blockchain.get_prev_hash() << std::endl;

        #endif
    }

    #ifdef USING_SERVER
    while (1) {}
    #else
    #endif

    return 0;
}