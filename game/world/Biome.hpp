//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <cstdint>

enum class Biome {
    Ocean,
    Plains,
    Forest,
    Mountains
};

Biome biomeAt(int x, int z, uint64_t seed);