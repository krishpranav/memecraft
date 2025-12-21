#include "ChunkManager.hpp"
#include "engine/threading/JobSystem.hpp"

ChunkManager::ChunkManager(uint64_t seed)
    : generator(seed) {}

void ChunkManager::update(int px, int pz) {
    const int radius = 2;

    for (int x = px - radius; x <= px + radius; x++) {
        for (int z = pz - radius; z <= pz + radius; z++) {
            long long k = key(x, z);
            if (chunks.find(k) == chunks.end()) {
                chunks[k] = std::make_unique<Chunk>(x, z);
                Chunk* c = chunks[k].get();

                JobSystem::submit([this, c]() {
                    generator.generate(*c);
                });
            }
        }
    }
}

Chunk* ChunkManager::getChunk(int x, int z) {
    auto it = chunks.find(key(x, z));
    return it != chunks.end() ? it->second.get() : nullptr;
}