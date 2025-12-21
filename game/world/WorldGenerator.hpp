//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include "Chunk.hpp"
#include <cstdint>

class WorldGenerator {
public:
    explicit WorldGenerator(uint64_t seed);
    void generate(Chunk& chunk);

private:
    uint64_t seed;
};