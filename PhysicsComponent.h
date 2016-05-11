//
// Created by cmarte on 5/30/15.
//

#ifndef FLATLAND_PHYSICSCOMPONENT_H
#define FLATLAND_PHYSICSCOMPONENT_H

#include "System.h"
#include "Geometry.h"

namespace fl {

    DEFINE_COMPONENT_OPTIONS(Physics)
    struct PhysicsOptions {
        double vx = 0, vy = 0;
        double gravity = 0;
        double bounce = 0;
        Box hitbox = {0,0};
        double friction = 0;
        double drag = 0; /* friction in air */
        bool center = false;
        Point offset = {0,0};
    };

    DEFAULT_COMPONENT_HANDLE(Physics)

}

#endif //FLATLAND_PHYSICSCOMPONENT_H
