#include <string>
// #include <atomic>

class Block {
    public:
        Block();

        int id;
        std::string prev_hash;
        Block* prev_block;

        std::string hash();
        void increment_nonce();
    
    private:
        int nonce;
        int timestamp;
};