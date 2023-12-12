#include <string>

class Block {
    public:
        int id;
        int timestamp;
        std::string prev_hash;
        int nonce;
        Block* prev_block;

        Block();
        std::string hash();
};