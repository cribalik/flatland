//
// Created by cmarte on 5/30/15.
//

#include "World.h"

namespace fl {

    EntityWrapper::EntityWrapper(World& w, Entity e)
    : _world(w)
    , _id(e)
    {}

    EntityWrapper::EntityWrapper(Entity e, World &w)
    : _world(w)
    , _id(e)
    {}

/* Convenience functions: add<System>Component(<System>Options) */
#define FL_SYSTEM(s) \
        s##Handle EntityWrapper::add##s##Component(const s##Options& opt) { \
            return _world.get##s##System().addComponent(_id, opt); \
        } \
        s##Handle EntityWrapper::add##s##Component(s##Options&& opt) { \
            return _world.get##s##System().addComponent(_id, std::move(opt)); \
        } \
        void EntityWrapper::remove##s##Component(s##Handle handle) { \
            _world.get##s##System().removeComponent(_id, handle); \
        } \
        s##Options EntityWrapper::get##s##Options(s##Handle handle) { \
            return _world.get##s##System().getOptions(_id, handle); \
        } \
        void EntityWrapper::set##s##Options(s##Handle handle, const s##Options& opt) { \
            _world.get##s##System().setOptions(_id, handle, opt); \
        }
#include "Systems.h"
#undef FL_SYSTEM

    void EntityWrapper::addUpdateListener(Updatable *updatable) {
        _world.addUpdateListener(_id, updatable);
    }

    void EntityWrapper::removeUpdateListener(Updatable *updatable) {
        _world.removeUpdateListener(updatable);
    }

    void EntityWrapper::removeUpdateListeners() {
        _world.removeUpdateListeners(_id);
    }

    Logic* EntityWrapper::_getLogic() {
        return _world.getLogicSystem().getLogic(_id);
    }

    const Tag& EntityWrapper::getTag() const {
        return _world.getTag(_id);
    }
    Tag& EntityWrapper::getTag() {
        return _world.getTag(_id);
    }

    void EntityWrapper::destroy() {
        _world.destroyEntity(_id);
    }

    Transform &EntityWrapper::getTransform() {
        return _world.getTransform(_id);
    }
}

