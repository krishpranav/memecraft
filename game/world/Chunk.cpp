#include "Chunk.hpp"

Chunk::Chunk(int x_, int z_) : x(x_), z(z_) {
    blocks.fill(0);
}

BlockID Chunk::get(int lx, int ly, int lz) const {
    return blocks[index(lx, ly, lz)];
}

void Chunk::set(int lx, int ly, int lz, BlockID id) {
    blocks[index(lx, ly, lz)] = id;
    dirty = true;
}