#pragma once

#include <array>
#include <cstdint>
#include <cassert>
#include "Block.hpp"
#include "engine/rendering/Mesh.hpp"

constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 16;
constexpr int CHUNK_SIZE_Z = 16;

constexpr size_t CHUNK_VOLUME =
    CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;

class Chunk {
public:
    Chunk(int cx, int cy, int cz) noexcept;

    BlockID get(int lx, int ly, int lz) const noexcept;
    void set(int lx, int ly, int lz, BlockID id) noexcept;

    const int x;
    const int y;
    const int z;

    bool dirty = true;
    bool generated = false;

    Mesh mesh;

private:
    std::array<BlockID, CHUNK_VOLUME> blocks{};

    constexpr size_t index(int lx, int ly, int lz) const noexcept {
        assert(lx >= 0 && lx < CHUNK_SIZE_X);
        assert(ly >= 0 && ly < CHUNK_SIZE_Y);
        assert(lz >= 0 && lz < CHUNK_SIZE_Z);
        return lx + CHUNK_SIZE_X * (lz + CHUNK_SIZE_Z * ly);
    }
};