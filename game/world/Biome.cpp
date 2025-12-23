//
// Created by Krisna Pranav on 21/12/25.
//

#include "Biome.hpp"
#include <cmath>

Biome biomeAt(int x, int z, uint64_t seed) {
    double n =
        std::sin((x + seed) * 0.001) +
        std::cos((z + seed) * 0.001);

    if (n < -0.6) return Biome::Ocean;
    if (n <  0.2) return Biome::Plains;
    if (n <  0.8) return Biome::Forest;
    return Biome::Mountains;
}