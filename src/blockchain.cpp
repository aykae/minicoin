#include "blockchain.h"

Blockchain::Blockchain() {
    length = 0;
    latest_block = nullptr;
    candidate_block = nullptr;
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
    candidate_block = block;
    return block;
}

int Blockchain::add_block() {
    latest_block = candidate_block;
    length++;

    return 1;
}