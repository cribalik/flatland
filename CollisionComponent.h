//
// Created by cmarte on 6/10/15.
//

#ifndef FLATLAND_COLLISIONCOMPONENT_H
#define FLATLAND_COLLISIONCOMPONENT_H

#include "System.h"

namespace fl {

    class CollisionListener;

    DEFAULT_COMPONENT_HANDLE(Collision);
    DEFINE_COMPONENT_OPTIONS(Collision)
    struct CollisionOptions {
        CollisionListener* listener;
    };
}

#endif //FLATLAND_COLLISIONCOMPONENT_H
