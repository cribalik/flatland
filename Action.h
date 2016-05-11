//
// Created by cmarte on 6/7/15.
//

#ifndef FLATLAND_ACTION_H
#define FLATLAND_ACTION_H

#include "EntityWrapper.h"

namespace fl {

    typedef void (*Action) (EntityWrapper);

    namespace action {
        /* Some common action */
        inline void exitProgram(EntityWrapper) { exit(0); }

        inline void destroyEntity(EntityWrapper e) { e.destroy(); }
    }
};
#endif //FLATLAND_ACTION_H
