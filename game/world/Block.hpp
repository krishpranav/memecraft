//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <string>
#include <cstdint>

using BlockID = uint16_t;

struct Block {
    BlockID id;
    std::string name;
    bool solid;
};