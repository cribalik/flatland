//
// Created by cmarte on 6/10/15.
//

#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include <tuple>
#include "World.h"

namespace fl {

    CollisionHandle CollisionSystem::addComponent(Entity e,
                                                                         const CollisionOptions &opt) {
        _data.insert(e, opt.listener);
    }

    void CollisionSystem::update(Time dt) {
        static std::vector<std::tuple<Entity, Entity, CollisionListener*>> to_call;
        to_call.clear();
        for (auto o : _data) {
            Entity e = o.first;
            CollisionListener* l = o.second;
            auto tr = _world.getTransform(e);
            PhysicsSystem::Data d = _world.getPhysicsSystem().getData(e);
            Rect r {tr.x - d.offset.x, tr.y - d.offset.y, d.hitbox.w, d.hitbox.h};

            for (auto& p : _data) {

                if (p.first == e) continue;
                PhysicsSystem::Data d = _world.getPhysicsSystem().getData(p.first);
                auto tr = _world.getTransform(p.first);
                auto le = tr.x - d.offset.x;
                auto ri = le + d.hitbox.w;
                auto to = tr.y - d.offset.y;
                auto bo = to + d.hitbox.h;
                if (!(r.x + r.w < le || r.x > ri || r.y > bo || r.y + r.h < to))
                    to_call.emplace_back(e, p.first, l);


            }
        }
        for (auto p : to_call)
            std::get<2>(p)->collision({_world, std::get<0>(p)}, {_world, std::get<1>(p)}, {});
    }

    CollisionHandle CollisionSystem::addComponent(Entity e, CollisionOptions &&opt) {this->addComponent(e, opt);}

    CollisionSystem::CollisionSystem(World &w) : _world(w) {}

    void CollisionSystem::removeEntity(Entity e) {_data.erase(e); }

}
