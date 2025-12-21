#include "Mesher.hpp"
#include "Chunk.hpp"

#include "engine/rendering/Vertex.hpp"

enum Face {
    PX, NX,
    PY, NY,
    PZ, NZ
};

bool Mesher::isAir(const Chunk& chunk, int x, int y, int z) const {
    if (x < 0 || x >= CHUNK_SIZE_X ||
        y < 0 || y >= CHUNK_SIZE_Y ||
        z < 0 || z >= CHUNK_SIZE_Z) {
        return true;
    }

    return chunk.get(x, y, z) == 0;
}

void Mesher::addFace(Chunk& chunk, int x, int y, int z, int face) {
    const uint32_t start =
        static_cast<uint32_t>(chunk.mesh.vertices.size());

    auto v = [&](float dx, float dy, float dz) {
        chunk.mesh.vertices.push_back({
            static_cast<float>(x) + dx,
            static_cast<float>(y) + dy,
            static_cast<float>(z) + dz
        });
    };

    switch (face) {
        case PX: v(1,0,0); v(1,1,0); v(1,1,1); v(1,0,1); break;
        case NX: v(0,0,1); v(0,1,1); v(0,1,0); v(0,0,0); break;
        case PY: v(0,1,1); v(1,1,1); v(1,1,0); v(0,1,0); break;
        case NY: v(0,0,0); v(1,0,0); v(1,0,1); v(0,0,1); break;
        case PZ: v(1,0,1); v(1,1,1); v(0,1,1); v(0,0,1); break;
        case NZ: v(0,0,0); v(0,1,0); v(1,1,0); v(1,0,0); break;
    }

    chunk.mesh.indices.insert(chunk.mesh.indices.end(), {
        start, start + 1, start + 2,
        start, start + 2, start + 3
    });
}

void Mesher::buildMesh(Chunk& chunk) {
    chunk.mesh.clear();

    for (int x = 0; x < CHUNK_SIZE_X; ++x) {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
                if (chunk.get(x, y, z) == 0) continue;

                if (isAir(chunk, x + 1, y, z)) addFace(chunk, x, y, z, PX);
                if (isAir(chunk, x - 1, y, z)) addFace(chunk, x, y, z, NX);
                if (isAir(chunk, x, y + 1, z)) addFace(chunk, x, y, z, PY);
                if (isAir(chunk, x, y - 1, z)) addFace(chunk, x, y, z, NY);
                if (isAir(chunk, x, y, z + 1)) addFace(chunk, x, y, z, PZ);
                if (isAir(chunk, x, y, z - 1)) addFace(chunk, x, y, z, NZ);
            }
        }
    }
}