#include "block.h"

#include <chrono>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

Block::Block(const int id, Block* latest_block){
    this->id = id;
    timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    nonce = 0;

    prev_hash = "";
    if (latest_block != nullptr) {
        prev_hash = latest_block->get_prev_hash();
    }
    prev_block = latest_block;
}

std::string Block::compute_hash()
{
    CryptoPP::SHA256 hash;
    std::string digest;

    std::string message = std::to_string(id) + std::to_string(timestamp) + prev_hash + std::to_string(nonce);

    CryptoPP::StringSource s(message, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    return digest;
}

int Block::get_timestamp() {
    return timestamp;
}

std::string Block::get_prev_hash() {
    return prev_hash;
}

void Block::increment_nonce() {
    nonce++;
}