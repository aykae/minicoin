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
    std::string hash = block->compute_hash();
    return hash.substr(hash.length()-difficulty, difficulty) == std::string(difficulty, '0');
}

void setup_server(httplib::Server& svr, Blockchain* blockchain) {
    svr.Get("/mine", [&](const httplib::Request &, httplib::Response &res) {
        Block* candidate = blockchain->get_candidate_block();
        if (candidate) {
            res.set_content(fmt::format("{{\"hash\": \"{}\", \"number\": \"{}\", \"timestamp\": \"{}\"}}", candidate->get_hash(), candidate->get_number(), candidate->get_timestamp()), "application/json");
        }
        else {
            res.set_content("{\"message\": \"No candidate block currently exists.\"}", "application/json");
        }
        // try {
        //     res.set_content(fmt::format("{{\"hash\": \"{}\", \"blen\": \"{}\", \"timestamp\": \"{}\"}}", blockchain->get_prev_hash(), blockchain->get_length()), "application/json");
        // } catch (e) {
        //     res.set_content("{\"message\": \"error\"}", "application/json");
        // }
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

        while(!mine(block)) {continue;}
        blockchain.add_block();
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