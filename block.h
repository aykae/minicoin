#include <string>

class Block {
    public:
        int id;
        int timestamp;
        std::string prev_hash;
        Block* prev_block;

        Block();
};