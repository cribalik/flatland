//
// Created by cmarte on 5/30/15.
//

#ifndef FLATLAND_LOGICCOMPONENT_H
#define FLATLAND_LOGICCOMPONENT_H

#include "System.h"

namespace fl {

    DEFAULT_COMPONENT_HANDLE(Logic);

    class Logic;

    DEFINE_COMPONENT_OPTIONS(Logic)
    struct LogicOptions {
        Logic* ptr;
        LogicOptions(Logic* ptr) : ptr(ptr) {}
    };

};

#endif //FLATLAND_LOGICCOMPONENT_H
