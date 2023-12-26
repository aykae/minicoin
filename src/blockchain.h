#include "block.h"
#include <string>

class Blockchain {
    public:
        Blockchain();

        int get_length();
        std::string get_prev_hash();
        Block* create_block();
        Block* get_candidate_block();
        int add_block();

    private:
        int length;
        Block* latest_block;
        Block* candidate_block;
};