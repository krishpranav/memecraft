#include "Mesher.hpp"
#include "Chunk.hpp"

#include "engine/rendering/Vertex.hpp"

enum Face {
    PX, NX,
    PY, NY,
    PZ, NZ
};

static bool isCrossPlant(BlockID id) {
    return id == 9;
}

bool Mesher::isAir(const Chunk& chunk, int x, int y, int z) const {
    if (y < 0 || y >= CHUNK_SIZE_Y)
        return true;

    if (x < 0 || x >= CHUNK_SIZE_X ||
        z < 0 || z >= CHUNK_SIZE_Z)
        return true;

    return chunk.get(x, y, z) == 0;
}

void Mesher::addFace(Chunk& chunk, int x, int y, int z, int face) {
    const uint32_t start =
        static_cast<uint32_t>(chunk.mesh.vertices.size());

    auto v = [&](float dx, float dy, float dz, float vType) {
        chunk.mesh.vertices.push_back({
            static_cast<float>(x) + dx,
            static_cast<float>(y) + dy,
            static_cast<float>(z) + dz,
            dx, vType
        });
    };

    switch (face) {
        case PX:
            v(1,0,0, 0.5f); v(1,1,0, 0.5f); v(1,1,1, 0.5f); v(1,0,1, 0.5f);
            break;
        case NX:
            v(0,0,1, 0.5f); v(0,1,1, 0.5f); v(0,1,0, 0.5f); v(0,0,0, 0.5f);
            break;
        case PY:
            v(0,1,1, 0.0f); v(1,1,1, 0.0f); v(1,1,0, 0.0f); v(0,1,0, 0.0f);
            break;
        case NY:
            v(0,0,0, 1.0f); v(1,0,0, 1.0f); v(1,0,1, 1.0f); v(0,0,1, 1.0f);
            break;
        case PZ:
            v(1,0,1, 0.5f); v(1,1,1, 0.5f); v(0,1,1, 0.5f); v(0,0,1, 0.5f);
            break;
        case NZ:
            v(0,0,0, 0.5f); v(0,1,0, 0.5f); v(1,1,0, 0.5f); v(1,0,0, 0.5f);
            break;
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
                // if (chunk.get(x, y, z) == 0) continue;

                BlockID id = chunk.get(x, y, z);
                if (id == 0) continue;

                if (isCrossPlant(id)) {
                    addFace(chunk, x, y, z, PX);
                    addFace(chunk, x, y, z, NX);
                    addFace(chunk, x, y, z, PZ);
                    addFace(chunk, x, y, z, NZ);
                    continue;
                }

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