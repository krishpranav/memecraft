//
// Created by Krisna Pranav on 21/12/25.
//

#include "BlockRegistry.hpp"
#include <stdexcept>

std::unordered_map<BlockID, Block> BlockRegistry::blocks;

void BlockRegistry::init() {
    blocks[0] = {0, "Air",   false};
    blocks[1] = {1, "Stone", true};
    blocks[2] = {2, "Dirt",  true};
    blocks[3] = {3, "Grass", true};
    blocks[4] = {4, "Sand",  true};
    blocks[5] = {5, "Water", false};

    blocks[6] = {6, "Log",   true};
    blocks[7] = {7, "Leaves",false};
    blocks[8] = {8, "Snow",  true};
    blocks[9] = {9, "TallGrass", false};
}

const Block& BlockRegistry::get(BlockID id) {
    auto it = blocks.find(id);
    if (it == blocks.end()) {
        throw std::runtime_error("Unknown BlockID");
    }
    return it->second;
}