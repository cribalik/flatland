//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_IDFACTORY_H
#define FLATLAND_IDFACTORY_H

#include <vector>
#include "Macros.h"

namespace fl {

    typedef std::size_t ID;

    class IDFactory {

        static std::vector<ID> _free;
        static ID _next;
        /* in-class initialization is not allowed,
         * so this is a hack to do it anyway
         * and keep this a header-only class */
        STATIC_INITIALIZE(_next = 0)

    public:

        static ID getID() {
            if (_free.empty())
                return _next++;
            ID id = _free.back();
            _free.pop_back();
            return id;
        }

        static void returnID(ID id) {
            _free.push_back(id);
        }

    };

}

#endif //FLATLAND_IDFACTORY_H
