#include <string>

class Block {
    public:
        Block(const int id, Block* latest_block);

        std::string compute_hash();
        int get_timestamp();
        std::string get_prev_hash();
        void increment_nonce();
    
    private:
        int id;
        int timestamp;
        int nonce;

        std::string prev_hash;
        Block* prev_block;
};