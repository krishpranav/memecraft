#include "Chunk.hpp"

Chunk::Chunk(int cx, int cy, int cz) noexcept
    : x(cx), y(cy), z(cz) {
    blocks.fill(0);
}

BlockID Chunk::get(int lx, int ly, int lz) const noexcept {
    return blocks[index(lx, ly, lz)];
}

void Chunk::set(int lx, int ly, int lz, BlockID id) noexcept {
    blocks[index(lx, ly, lz)] = id;
    dirty = true;
}