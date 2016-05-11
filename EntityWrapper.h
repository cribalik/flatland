//
// Created by cmarte on 5/26/15.
//

#ifndef FLATLAND_ENTITYWRAPPER_H
#define FLATLAND_ENTITYWRAPPER_H

#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "LogicComponent.h"
#include "TextComponent.h"
#include "CollisionComponent.h"

namespace fl {

    class World;
    class Updatable;

    class EntityWrapper {
        World& _world;
        Entity _id;
    public:

        EntityWrapper(World& w, Entity e);
        EntityWrapper(Entity e, World& w);

        operator Entity() const {return _id;}

        World& world() {return _world;}
        const Entity& entity() const {return _id;}

        void destroy();

        Transform& getTransform();

        void addUpdateListener(Updatable*);
        void removeUpdateListener(Updatable*);
        void removeUpdateListeners();

        template<typename T> T* getLogic() {return dynamic_cast<T*>(_getLogic());};

        Tag& getTag();
        const Tag& getTag() const;
        /* Convenience functions: add<System>Component(<System>Options) */
        #define FL_SYSTEM(s) \
        s##Handle add##s##Component(const s##Options& opt); \
        s##Handle add##s##Component(s##Options&& opt); \
        void remove##s##Component(s##Handle handle); \
        s##Options get##s##Options(s##Handle handle); \
        void set##s##Options(s##Handle handle, const s##Options& opt);
        #include "Systems.h"
        #undef FL_SYSTEM

    private:
        Logic* _getLogic();
    };

}

#endif //FLATLAND_ENTITYWRAPPER_H
