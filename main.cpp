#include "block.h"
#include <iostream>

int main() {
    Block genesis;

    Block b1;
    b1.id = 1;
    b1.prev_block = &genesis;

    std::cout << b1.id << std::endl;
    std::cout << b1.prev_block->id << std::endl;
    std::cout << b1.hash() << std::endl;
}