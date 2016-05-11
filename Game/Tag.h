//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_TAG_H
#define FLATLAND_TAG_H

#include <cstdint>

enum class Tag : std::size_t {
    #define TAG(t) t,
    #include "DefaultTags.h"
    #include "Tags.h"
    #undef TAG
};

extern const char* gTagNames[];

#endif //FLATLAND_TAG_H
