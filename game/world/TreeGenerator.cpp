//
// Created by Krisna Pranav on 21/12/25.
//

#include "TreeGenerator.hpp"

void TreeGenerator::placeTree(Chunk& chunk, int x, int y, int z) {

    // Trunk
    for (int i = 0; i < 4; ++i) {
        if (y + i < CHUNK_SIZE_Y)
            chunk.set(x, y + i, z, 1); // Stone as wood placeholder
    }

    // Leaves (simple cube)
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dz = -2; dz <= 2; ++dz) {
            for (int dy = 2; dy <= 4; ++dy) {
                int lx = x + dx;
                int ly = y + dy;
                int lz = z + dz;

                if (lx < 0 || lx >= CHUNK_SIZE_X ||
                    lz < 0 || lz >= CHUNK_SIZE_Z ||
                    ly < 0 || ly >= CHUNK_SIZE_Y)
                    continue;

                chunk.set(lx, ly, lz, 3); // Grass as leaf placeholder
            }
        }
    }
}