#include "block.h"
#include <iostream>

int difficulty = 10;

int mine(Block& block) {
    block.increment_nonce();
    std::string hash = block.hash();

    return hash.substr(hash.length()-difficulty, difficulty) == std::string(difficulty, '0');
}

int main() {

    Block genesis;

    Block b1;
    b1.id = 1;
    b1.prev_block = &genesis;

    // std::cout << b1.id << std::endl;
    // std::cout << b1.prev_block->id << std::endl;
    // std::cout << b1.hash() << std::endl;

    while (!mine(genesis))  {}
    b1.prev_hash = genesis.hash();

    std::cout << b1.prev_hash << std::endl;
    std::cout << std::string(difficulty, '0') << std::endl;
}