#include "WorldGenerator.hpp"
#include "Chunk.hpp"

#include <cmath>

WorldGenerator::WorldGenerator(uint64_t seed_) : seed(seed_) {}

static int heightAt(int x, int z, uint64_t seed) {
    double n = std::sin(x * 0.01 + seed) + std::cos(z * 0.01 + seed);
    return 64 + static_cast<int>(n * 10);
}

void WorldGenerator::generate(Chunk& chunk) {
    for (int x = 0; x < CHUNK_SIZE_X; ++x) {
        for (int z = 0; z < CHUNK_SIZE_Z; ++z) {

            int wx = chunk.x * CHUNK_SIZE_X + x;
            int wz = chunk.z * CHUNK_SIZE_Z + z;
            int h  = heightAt(wx, wz, seed);

            for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
                if (y < h - 1) {
                    chunk.set(x, y, z, 1); // Stone
                } else if (y == h - 1) {
                    chunk.set(x, y, z, 2); // Dirt
                } else if (y == h) {
                    chunk.set(x, y, z, 3); // Grass
                }
            }
        }
    }

    chunk.generated = true;
}