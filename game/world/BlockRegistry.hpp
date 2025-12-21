//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include "Block.hpp"
#include <unordered_map>

class BlockRegistry {
public:
    static void init();
    static const Block& get(BlockID id);

private:
    static std::unordered_map<BlockID, Block> blocks;
};