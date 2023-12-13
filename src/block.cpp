#include "block.h"
#include <chrono>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

Block::Block() {
    id = 0;
    timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    prev_hash = "";
    prev_block = nullptr;
    nonce = 0;
}

void Block::increment_nonce() {
    nonce.store(nonce.load() + 1);
    //nonce++;
}

std::string Block::hash()
{
    CryptoPP::SHA256 hash;
    std::string digest;

    std::string message = std::to_string(id) + std::to_string(timestamp) + prev_hash + std::to_string(nonce.load());

    CryptoPP::StringSource s(message, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    return digest;
}