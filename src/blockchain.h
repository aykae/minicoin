#include "block.h"
#include <string>

class Blockchain {
    public:
        Blockchain();

        int get_length();
        std::string get_prev_hash();
        Block* create_block();
        int add_block(Block* block);

    private:
        int length;
        Block* latest_block;
};