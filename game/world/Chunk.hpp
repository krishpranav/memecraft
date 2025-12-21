#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cassert>

#include "Block.hpp"
#include "engine/rendering/Mesh.hpp"

constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 256;
constexpr int CHUNK_SIZE_Z = 16;

constexpr size_t CHUNK_VOLUME =
    static_cast<size_t>(CHUNK_SIZE_X) *
    static_cast<size_t>(CHUNK_SIZE_Y) *
    static_cast<size_t>(CHUNK_SIZE_Z);

class Chunk {
public:
    Chunk(int chunkX, int chunkZ) noexcept;

    [[nodiscard]] BlockID get(int lx, int ly, int lz) const noexcept;
    void set(int lx, int ly, int lz, BlockID id) noexcept;

    const int x; // Chunk X coordinate in world space
    const int z; // Chunk Z coordinate in world space

    bool dirty     = true;  // Mesh needs rebuild
    bool generated = false; // Terrain generation completed

    Mesh mesh;

private:
    std::array<BlockID, CHUNK_VOLUME> blocks{};

    [[nodiscard]] constexpr size_t index(int lx, int ly, int lz) const noexcept {
        assert(lx >= 0 && lx < CHUNK_SIZE_X);
        assert(ly >= 0 && ly < CHUNK_SIZE_Y);
        assert(lz >= 0 && lz < CHUNK_SIZE_Z);

        return static_cast<size_t>(
            lx +
            CHUNK_SIZE_X * (lz + CHUNK_SIZE_Z * ly)
        );
    }
};