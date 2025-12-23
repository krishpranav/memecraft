#include "ChunkManager.hpp"
#include "engine/threading/JobSystem.hpp"

ChunkManager::ChunkManager(uint64_t seed)
    : generator(seed) {}

void ChunkManager::update(int pcx, int pcz) {

    const int radius = 8;
    const int vRadius = 8;

    for (int cx = pcx - radius; cx <= pcx + radius; ++cx) {
        for (int cz = pcz - radius; cz <= pcz + radius; ++cz) {

            auto& column = columns[key(cx, cz)];

            for (int cy = -vRadius; cy <= vRadius; ++cy) {
                if (column.vertical.count(cy)) continue;

                auto chunk = std::make_unique<Chunk>(cx, cy, cz);
                Chunk* ptr = chunk.get();
                column.vertical[cy] = std::move(chunk);

                JobSystem::submit([this, ptr]() {
                    generator.generate(*ptr);
                });
            }
        }
    }
}

void ChunkManager::forEachChunk(const std::function<void(Chunk&)>& fn) const {
    for (auto& [_, col] : columns) {
        for (auto& [__, chunk] : col.vertical) {
            if (chunk && chunk->generated)
                fn(*chunk);
        }
    }
}

Chunk* ChunkManager::getChunk(int cx, int cy, int cz) const {
    auto colIt = columns.find(key(cx, cz));
    if (colIt == columns.end()) return nullptr;

    auto it = colIt->second.vertical.find(cy);
    if (it == colIt->second.vertical.end()) return nullptr;

    return it->second.get();
}

BlockID ChunkManager::getBlock(int wx, int wy, int wz) const {

    int cx = floorDiv(wx, CHUNK_SIZE_X);
    int cy = floorDiv(wy, CHUNK_SIZE_Y);
    int cz = floorDiv(wz, CHUNK_SIZE_Z);

    int lx = mod(wx, CHUNK_SIZE_X);
    int ly = mod(wy, CHUNK_SIZE_Y);
    int lz = mod(wz, CHUNK_SIZE_Z);

    Chunk* c = getChunk(cx, cy, cz);
    if (!c || !c->generated) return 0;

    return c->get(lx, ly, lz);
}

void ChunkManager::setBlock(int wx, int wy, int wz, BlockID id) {

    int cx = floorDiv(wx, CHUNK_SIZE_X);
    int cy = floorDiv(wy, CHUNK_SIZE_Y);
    int cz = floorDiv(wz, CHUNK_SIZE_Z);

    int lx = mod(wx, CHUNK_SIZE_X);
    int ly = mod(wy, CHUNK_SIZE_Y);
    int lz = mod(wz, CHUNK_SIZE_Z);

    Chunk* c = getChunk(cx, cy, cz);
    if (!c || !c->generated) return;

    c->set(lx, ly, lz, id);
}

int ChunkManager::getSurfaceHeight(int wx, int wz) const {

    for (int cy = 32; cy >= -32; --cy) {
        for (int ly = CHUNK_SIZE_Y - 1; ly >= 0; --ly) {
            int wy = cy * CHUNK_SIZE_Y + ly;
            if (getBlock(wx, wy, wz) != 0)
                return wy;
        }
    }
    return 0;
}

int ChunkManager::getTerrainHeight(int wx, int wz) const {
    return generator.getHeightAt(wx, wz);
}