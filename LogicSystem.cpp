//
// Created by cmarte on 5/30/15.
//

#include "LogicSystem.h"

namespace fl {

    LogicHandle LogicSystem::addComponent(Entity e, const LogicOptions & opt) {
        _ptrs.insert(e, opt.ptr);
    }

    LogicHandle LogicSystem::addComponent(Entity e, LogicOptions && opt) {
        this->addComponent(e, opt);
    }

    void LogicSystem::removeEntity(Entity e) {
        Logic* p = _ptrs[e];
        if (!p) return;
        p->logicDestroy({_world, e});
        _ptrs.erase(e);
    }

    void LogicSystem::update(Time) {}

    LogicSystem::LogicSystem(World &w) : _world(w) {}

};