#include "block.h"

class Blockchain {
    public:
        Blockchain();
        int get_length();
        int add_block(Block* block);
    private:
        Block* latest_block;
        int length;
};