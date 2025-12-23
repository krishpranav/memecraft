#include "Collision.hpp"

bool isSolidBlock(const ChunkManager& world, int wx, int wy, int wz) {

    int cx = ChunkManager::floorDiv(wx, CHUNK_SIZE_X);
    int cy = ChunkManager::floorDiv(wy, CHUNK_SIZE_Y);
    int cz = ChunkManager::floorDiv(wz, CHUNK_SIZE_Z);

    int lx = ChunkManager::mod(wx, CHUNK_SIZE_X);
    int ly = ChunkManager::mod(wy, CHUNK_SIZE_Y);
    int lz = ChunkManager::mod(wz, CHUNK_SIZE_Z);

    Chunk* c = world.getChunk(cx, cy, cz);
    if (!c || !c->generated) return false;

    return c->get(lx, ly, lz) != 0;
}