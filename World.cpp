//
// Created by cmarte on 5/26/15.
//

#include "World.h"

namespace fl {

    World::World(Window &window)
            : _window(window)
              /* Initialize systems */
#define FL_SYSTEM(s) \
            , _##s##System(*this)

#include "Systems.h"
#undef FL_SYSTEM
    {
        /* SDL Should be loaded */
        if (!SDL_WasInit(SDL_INIT_EVERYTHING))
                DEBUGLOG_AND_DIE("SDL was not inited. ", SDL_GetError(), " Exiting");
        SDL_RenderSetLogicalSize(window.getRenderer(), 1920, 1080);
        window.show();
    }


    void World::run() {

        Time t1 = SDL_GetTicks();
        /* Main loop */
        while (1) {
            Time t2 = SDL_GetTicks();
            tick(std::max(t2 - t1, (Time)14));
            t1 = SDL_GetTicks();
            /* wait remaining time of frame */
            if (t1 - t2 < _frametime) SDL_Delay(_frametime - (t1-t2));
        }

    }

    EntityWrapper World::createEntity(Tag tag, Transform tr, Logic* l) {
        Entity e = _entityFactory.create();
        _tags.insert(e, tag);
        _transforms.insert(e, tr);
        _LogicSystem.addComponent(e, {l});
        return {*this, e};
    }

    void World::destroyEntity(Entity e) {
        _removeQueue.push_back(e);
    }

    void World::_execEvents() {
        while (!_eventQueue.empty() && _eventQueue.top().time <= _time) {
            _eventQueue.top().action(EntityWrapper(*this, _eventQueue.top().target));
            _eventQueue.pop();
        }
    }

    void World::_removeQueued() {
        if (_removeQueue.empty()) return;
        DEBUGLOG("Removing entities...\n");
        /* Only unique items */
        _removeQueue.resize(std::unique(_removeQueue.begin(), _removeQueue.end()) - _removeQueue.begin());
        for (Entity e : _removeQueue) {
            _entityFactory.giveBack(e);
            /* remove queued events targeting this Entity */
            _eventQueue.remove_if([e](const Event &pE) {
                return pE.target == e;
            });
            /* Remove update listeners */
            _updateListeners.resize(
                    std::remove_if(_updateListeners.begin(), _updateListeners.end(),
                                   [e](const std::pair<Entity, Updatable *> &p) {
                                       return p.first == e;
                                   }) - _updateListeners.begin()
            );
            /* Remove entity from systems */
#define FL_SYSTEM(s) \
            _##s##System.removeEntity(e);

#include "Systems.h"

#undef FL_SYSTEM
        }
        _removeQueue.clear();
    }

    void World::addUpdateListener(Entity e, Updatable *l) {
        _updateListeners.emplace_back(e, l);
        _updateListeners.back().second->updateInit({*this, e});
    }

    void World::removeUpdateListener(Updatable *l) {
        auto end = std::remove_if(_updateListeners.begin(), _updateListeners.end(),
                                  [l](const std::pair<Entity, Updatable *> &p) {
                                      return p.second == l;
                                  });
        for (; end != _updateListeners.end(); ++end)
            end->second->updateDestroy({*this, end->first});
    }

    void World::removeUpdateListeners(Entity e) {
        auto end = std::remove_if(_updateListeners.begin(), _updateListeners.end(),
                                  [e](const std::pair<Entity, Updatable *> &p) {
                                      return p.first == e;
                                  });
        for (; end != _updateListeners.end(); ++end)
            end->second->updateDestroy({*this, end->first});
    }

    void World::tick(Time dt) {

        /* Update time TODO: do better here */
        _time += dt;

        /* Process queued entity removals */
        this->_removeQueued();

        /* Process queued events */
        this->_execEvents();

        /* Clear draw buffer and set draw color */
        SDL_SetRenderDrawColor(getRenderer(), 0,0,0,255);
        SDL_RenderClear(getRenderer());

        /* Update listeners */
        for (std::pair<Entity, Updatable *> u : _updateListeners)
            u.second->update({*this, u.first}, dt);

        /* Update systems */
#define FL_SYSTEM(s) \
            _##s##System.update(dt);

#include "Systems.h"

#undef FL_SYSTEM

        /* Draw */
        SDL_RenderPresent(getRenderer());
    }
}
