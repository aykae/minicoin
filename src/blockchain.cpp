#include "blockchain.h"

Blockchain::Blockchain() {
    length = 0;
}

int Blockchain::get_length() {
    return length;
}

int Blockchain::add_block(Block* block) {
    if (get_length()) { // New Block
        block->prev_block = latest_block;
        latest_block = block;
    }
    else { //Genesis Block
        latest_block = block;
        length++;
    }

    return 1;
}