#pragma once
#include <array>
#include "Block.hpp"

constexpr int CHUNK_X = 16;
constexpr int CHUNK_Y = 256;
constexpr int CHUNK_Z = 16;

class Chunk {
public:
    Chunk(int x, int z);

    BlockID get(int x, int y, int z) const;
    void set(int x, int y, int z, BlockID id);

    int x, z;
    bool dirty = true;

private:
    std::array<BlockID, CHUNK_X * CHUNK_Y * CHUNK_Z> blocks;

    int index(int lx, int ly, int lz) const {
        return lx + CHUNK_X * (lz + CHUNK_Z * ly);
    }
};