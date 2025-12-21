//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include "Chunk.hpp"
#include "WorldGenerator.hpp"
#include <unordered_map>
#include <memory>

class ChunkManager {
public:
    explicit ChunkManager(uint64_t seed);
    void update(int playerChunkX, int playerChunkZ);

    Chunk* getChunk(int x, int z);

private:
    std::unordered_map<long long, std::unique_ptr<Chunk>> chunks;
    WorldGenerator generator;

    long long key(int x, int z) const {
        return (static_cast<long long>(x) << 32) |
            static_cast<unsigned int>(z);
    }
};