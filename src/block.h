#include <string>
// #include <atomic>

class Block {
    public:
        int id;
        std::string prev_hash;
        Block* prev_block;

        Block();
        std::string hash();
        void increment_nonce();
    
    private:
        int nonce;
        int timestamp;
};