//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once
#include "game/world/ChunkManager.hpp"
#include "game/world/Mesher.hpp"

class WorldSystem {
public:
    explicit WorldSystem(uint64_t seed);

    void update(int playerChunkX, int playerChunkZ);

private:
    ChunkManager chunkManager;
    Mesher mesher;
};