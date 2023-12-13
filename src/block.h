#include <string>
#include <atomic>

class Block {
    public:
        int id;
        std::string prev_hash;
        Block* prev_block;
        std::atomic<int> nonce;

        Block();
        std::string hash();
        void increment_nonce();
    
    private:
        int timestamp;
};