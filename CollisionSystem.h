//
// Created by cmarte on 6/10/15.
//

#ifndef FLATLAND_COLLISIONSYSTEM_H
#define FLATLAND_COLLISIONSYSTEM_H

#include <Utility/ContiguousMap.h>
#include "EntityWrapper.h"

namespace fl {

    struct CollisionData {};
    class CollisionListener {
    public:
        virtual void CollisionInit (EntityWrapper) = 0;
        virtual void CollisionDestroy (EntityWrapper) = 0;
        virtual void collision(EntityWrapper me, EntityWrapper other, const CollisionData&) = 0;
    };

class CollisionSystem {

    ContiguousMap<CollisionListener*, Entity> _data;
public:

    DECLARE_SYSTEM_METHODS_DEFAULT_HANDLE(Collision)

};

}

#endif //FLATLAND_COLLISIONSYSTEM_H
