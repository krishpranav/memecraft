#include "WorldSystem.hpp"

WorldSystem::WorldSystem(uint64_t seed)
    : chunkManager(seed) {}

void WorldSystem::update(int pcx, int pcz) {
    chunkManager.update(pcx, pcz);

    chunkManager.forEachChunk([this](Chunk& chunk) {
        if (chunk.dirty) {
            mesher.buildMesh(chunk);
            chunk.dirty = false;
        }
    });
}