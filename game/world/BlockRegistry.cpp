//
// Created by Krisna Pranav on 21/12/25.
//

#include "BlockRegistry.hpp"
#include <stdexcept>

std::unordered_map<BlockID, Block> BlockRegistry::blocks;

void BlockRegistry::init() {
    blocks[0] = {0, "Air", false};
    blocks[0] = {1, "Stone", true};
    blocks[0] = {2, "Dirt", true};
    blocks[0] = {3, "Grass", true};
}

const Block& BlockRegistry::get(BlockID id) {
    auto it = blocks.find(id);
    if (it == blocks.end()) {
        throw std::runtime_error("Unknown BlockID");
    }
    return it->second;
}