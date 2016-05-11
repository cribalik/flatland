//
// Created by cmarte on 5/27/15.
//

#include "Tag.h"

const char * gTagNames[] = {
    #define TAG(t) #t,
    #include "DefaultTags.h"
    #include "Tags.h"
    #undef TAG
};
