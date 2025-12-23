#pragma once

#include "Chunk.hpp"
#include "WorldGenerator.hpp"
#include <unordered_map>
#include <memory>
#include <functional>

class ChunkManager {
public:
    explicit ChunkManager(uint64_t seed);

    void update(int pcx, int pcz);
    void forEachChunk(const std::function<void(Chunk&)>& fn) const;

    Chunk* getChunk(int cx, int cy, int cz) const;

    BlockID getBlock(int wx, int wy, int wz) const;
    void setBlock(int wx, int wy, int wz, BlockID id);

    int getSurfaceHeight(int wx, int wz) const;
    int getTerrainHeight(int wx, int wz) const;

    static int floorDiv(int a, int b) {
        return (a >= 0) ? a / b : ((a + 1) / b - 1);
    }

    static int mod(int a, int b) {
        int m = a % b;
        return m < 0 ? m + b : m;
    }

private:
    struct Column {
        std::unordered_map<int, std::unique_ptr<Chunk>> vertical;
    };

    std::unordered_map<long long, Column> columns;
    WorldGenerator generator;

    static long long key(int cx, int cz) {
        return (static_cast<long long>(cx) << 32) |
               static_cast<unsigned int>(cz);
    }
};