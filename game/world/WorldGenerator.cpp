#include "WorldGenerator.hpp"
#include "BlockRegistry.hpp"
#include "Biome.hpp"
#include "TreeGenerator.hpp"

#include <cmath>
#include <algorithm>

static constexpr int SEA_LEVEL  = 62;
static constexpr int MAX_HEIGHT = 180;

static double clamp(double v, double a, double b) {
    return std::max(a, std::min(v, b));
}

static double baseNoise(double x, double z, uint64_t seed) {
    return std::sin(x + seed * 0.17) * std::cos(z + seed * 0.31);
}

static double fbm(double x, double z, uint64_t seed) {
    double value = 0.0;
    double amplitude = 1.0;
    double frequency = 1.0;

    for (int i = 0; i < 5; ++i) {
        value += baseNoise(x * frequency, z * frequency, seed + i * 101) * amplitude;
        amplitude *= 0.5;
        frequency *= 2.0;
    }

    return value;
}

static int heightAt(int x, int z, uint64_t seed, Biome biome) {
    double wx = x + fbm(x * 0.01, z * 0.01, seed + 1000) * 40.0;
    double wz = z + fbm(x * 0.01, z * 0.01, seed + 2000) * 40.0;

    double continental = fbm(wx * 0.001, wz * 0.001, seed) * 60.0;

    double hills = fbm(wx * 0.01, wz * 0.01, seed + 300) * 30.0;

    double detail = fbm(wx * 0.05, wz * 0.05, seed + 900) * 6.0;

    double biomeBias  = 0.0;
    double biomeScale = 1.0;

    switch (biome) {
        case Biome::Ocean:
            biomeBias  = -30.0;
            biomeScale = 0.3;
            break;
        case Biome::Plains:
            biomeScale = 0.6;
            break;
        case Biome::Forest:
            biomeBias  = 6.0;
            biomeScale = 0.9;
            break;
        case Biome::Mountains:
            biomeBias  = 40.0;
            biomeScale = 1.5;
            break;
    }

    double height =
        64.0 +
        continental * biomeScale +
        hills       * biomeScale +
        detail +
        biomeBias;

    return static_cast<int>(clamp(height, 5.0, MAX_HEIGHT));
}

WorldGenerator::WorldGenerator(uint64_t seed_)
    : seed(seed_) {}

void WorldGenerator::generate(Chunk& chunk) {

    const int baseX = chunk.x * CHUNK_SIZE_X;
    const int baseY = chunk.y * CHUNK_SIZE_Y;
    const int baseZ = chunk.z * CHUNK_SIZE_Z;

    for (int x = 0; x < CHUNK_SIZE_X; ++x) {
        for (int z = 0; z < CHUNK_SIZE_Z; ++z) {

            int wx = baseX + x;
            int wz = baseZ + z;

            Biome biome = biomeAt(wx, wz, seed);
            int surface = heightAt(wx, wz, seed, biome);

            for (int y = 0; y < CHUNK_SIZE_Y; ++y) {

                int wy = baseY + y;
                BlockID id = 0;

                if (wy <= surface) {

                    if (biome == Biome::Mountains && wy > surface - 2 && surface > 140) {
                        id = 1;
                    }
                    else if (wy == surface) {
                        id = (biome == Biome::Ocean) ? 4 : 3;
                    }
                    else if (wy > surface - 4) {
                        id = 2;
                    }
                    else {
                        id = 1;
                    }
                }

                if (wy > surface && wy <= SEA_LEVEL && biome == Biome::Ocean) {
                    id = 5;
                }

                if (id != 0) {
                    chunk.set(x, y, z, id);
                }
            }

            if (biome == Biome::Forest && surface > SEA_LEVEL + 2) {
                uint64_t hash =
                    static_cast<uint64_t>(wx) * 734287u ^
                    static_cast<uint64_t>(wz) * 912931u ^
                    seed;

                if ((hash & 63u) == 0u) {
                    TreeGenerator::placeTree(
                        chunk,
                        x,
                        surface - baseY + 1,
                        z
                    );
                }
            }
        }
    }

    chunk.generated = true;
    chunk.dirty = true;
}

int WorldGenerator::getHeightAt(int wx, int wz) const {
    Biome biome = biomeAt(wx, wz, seed);
    return heightAt(wx, wz, seed, biome);
}