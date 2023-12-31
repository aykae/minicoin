#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include "blockchain.h"
#include <iostream>
#include <fmt/core.h>
#include <mutex>

#define USING_SERVER

int difficulty = 5;
std::mutex blockMutex;

//eventually move to miner class
int mine(Block* block) {
    block->increment_nonce();
    block->compute_hash();
    return block->get_hash().substr(0, difficulty) == std::string(difficulty, '0');
}

void setup_server(httplib::Server& svr, Blockchain* blockchain) {
    svr.Get("/mine", [&](const httplib::Request &, httplib::Response &res) {
        Block* candidate = blockchain->get_candidate_block();
        if (candidate) {
            res.set_content(fmt::format("{{\"hash\": \"{}\", \"number\": \"{}\", \"timestamp\": \"{}\", \"prevHash\": \"{}\"}}", candidate->get_hash(), candidate->get_number(), candidate->get_timestamp(), candidate->get_prev_hash()), "application/json");
        }
        else {
            res.set_content("{\"message\": \"No candidate block currently exists.\"}", "application/json");
        }
    });

    svr.listen("localhost", 8080);
}

//Note: is a snapchat of the block pointer taken upon initializaiton? I'm not sure why this endpoint wouldn't update as the data to which the pointer points changes
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
    std::thread server_thread([&] {
        setup_server(svr, &blockchain);
    });
    server_thread.detach();

    #else
    #endif

    std::cout << "Blockchain generated." << std::endl;

    while (1) {
        Block* block = blockchain.create_block();

        #ifdef USING_SERVER
        #else
        #endif

        while(!mine(block)) {continue;}
        std::cout << "Block Number " << blockchain.get_candidate_block()->get_number() << ": " << blockchain.get_candidate_block()->get_prev_hash() << std::endl;
        blockchain.add_block();
    }

    return 0;
}