#include <string>

class Block {
    public:
        Block(const int number, Block* latest_block);

        std::string compute_hash();
        std::string get_hash();
        int get_number();
        int get_timestamp();
        std::string get_prev_hash();
        void increment_nonce();
    
    private:
        int number;
        int timestamp;
        int nonce;
        std::string hash;

        std::string prev_hash;
        Block* prev_block;
};