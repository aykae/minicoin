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
}

std::string Block::hash()
{
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource s(std::to_string(Block::timestamp), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    return digest;
}