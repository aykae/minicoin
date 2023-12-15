#include "blockchain.h"

Blockchain::Blockchain() {
    length = 0;
    latest_block = nullptr;
}

int Blockchain::get_length() {
    return length;
}

std::string Blockchain::get_prev_hash() {
    if (latest_block != nullptr) {
        return latest_block->compute_hash();
    }
    return "";
}

Block* Blockchain::create_block() {
    Block* block = new Block(get_length(), latest_block);
    return block;
}

int Blockchain::add_block(Block* block) {
    if (get_length()) { // New Block
        latest_block = block;
        length++;
    }
    else { //Genesis Block
        latest_block = block;
        length++;
    }

    return 1;
}