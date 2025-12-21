//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include "Chunk.hpp"

class Mesher {
public:
    void buildMesh(Chunk& chunk);

private:
    bool isAir(const Chunk& chunk, int x, int y, int z) const;
    void addFace(Chunk& chunk, int x, int y, int z, int face);
};