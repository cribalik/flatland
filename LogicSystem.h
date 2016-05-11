//
// Created by cmarte on 5/30/15.
//

#ifndef FLATLAND_LOGICSYSTEM_H
#define FLATLAND_LOGICSYSTEM_H

#include "System.h"
#include "EntityWrapper.h"
#include "Utility/Table.h"
#include "LogicComponent.h"

namespace fl {

    class Logic {
    public:
        virtual void logicInit(EntityWrapper) = 0;
        virtual void logicDestroy(EntityWrapper) = 0;
    };

    class LogicSystem {

    private:

        Table<Logic*, Entity> _ptrs;

    public:

        DECLARE_SYSTEM_METHODS_DEFAULT_HANDLE(Logic)

        Logic* getLogic(Entity e) {return _ptrs[e];}

    };

}

#endif //FLATLAND_LOGICSYSTEM_H
