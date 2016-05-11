//
// Created by cmarte on 5/26/15.
//

#ifndef FLATLAND_WORLD_H
#define FLATLAND_WORLD_H

#include <functional>
#include <queue>
#include "fl_SDLInit.h"
#include "Core.h"
#include "PhysicsSystem.h"
#include "SpriteSystem.h"
#include "InputSystem.h"
#include "LogicSystem.h"
#include "TextSystem.h"
#include "CollisionSystem.h"
#include "Window.h"
#include "Utility/Table.h"
#include "Utility/IndexFactory.h"
#include "Utility/Heap.h"
#include "EntityWrapper.h"
#include "Action.h"

namespace fl {

    class Window;

    class Updatable {
    public:
        virtual void updateInit(EntityWrapper) = 0;
        virtual void updateDestroy(EntityWrapper) = 0;
        virtual void update(EntityWrapper, Time) = 0;
    };

    class World {

    /*** Types ***/

    public:

        /* Timed event - time is the timepoint at which callback is to be called on the specified target */
        struct Event {
            Entity target;
            Action action;
            Time time;
            bool operator<(const Event& e) {return e.time < time;}
        };

    private:

        /* Milliseconds per frame */
        Time _frametime = 1000./60.;
        /* Elapsed time since start TODO: prevent overflow */
        Time _time = 0;
        Window& _window;
        /* Queued events */
        Heap<Event> _eventQueue;
        /* Queued entity removals */
        std::vector<Entity> _removeQueue;
        /* Update Listeners */
        std::vector<std::pair<Entity, Updatable*>> _updateListeners;

        /* member variables  <System>System _<System>System; */
#define FL_SYSTEM(s) \
        s##System _##s##System;
#include "Systems.h"
#undef FL_SYSTEM

        /* Global Entity properties */
        Table<Tag, Entity> _tags;
        Table<Transform, Entity> _transforms;

        /* Entity index factory */
        IndexFactory<Entity> _entityFactory;

    public:

        /* Constructor */
        World(fl::Window &window);

        /* Main loop */
        void run();

        /* Run a single tick, for use with user-defined Main loops */
        void tick(Time);

        /* Create and destroy entities */
        EntityWrapper createEntity(fl::Tag tag = 0, Transform tr = Transform(), Logic* logic = nullptr);
        void destroyEntity(Entity e);

        /* Window and renderer */
        Window& getWindow() {return _window;}
        Renderer& getRenderer() {return _window.getRenderer();}

        /* System getters <System>System& get<System>System() */
#define FL_SYSTEM(s) \
        s##System& get##s##System() { return _##s##System; }
#include "Systems.h"
#undef FL_SYSTEM

        /* Add to event queue */
        void addEvent(Entity target, Action action, Time t) { _eventQueue.push({target, action, t+_time}); };

        /* Add/Remove Update Listener */
        void addUpdateListener(Entity, Updatable*);
        void removeUpdateListener(Updatable*);
        void removeUpdateListeners(Entity);


        /* Getter and Setter for fps */
        /* FIXME: What if fps is 0??? */
        void setFPS(Time fps) {_frametime = Time(1000)/fps;}
        Time getFPS() {return Time(1000)/_frametime;}

        /* Getters and setters for Entity properties */
        Tag& getTag(Entity e) {return _tags[e];}
        Transform& getTransform(Entity e) {return _transforms[e];}

    private:
        void _removeQueued();
        void _execEvents();

        World(const World&) = delete;
    };

}

#endif //FLATLAND_WORLD_H
