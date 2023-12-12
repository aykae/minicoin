#include "block.h"
#include <chrono>

Block::Block() {
    id = 0;
    timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    prev_hash = "";
    prev_block = nullptr;
}