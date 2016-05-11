//
// Created by christopher on 2015-06-04.
//

#ifndef FLATLAND_ACTOR_H
#define FLATLAND_ACTOR_H

#include "GameObject.h"

class Actor;

struct HitData {
    Actor& hitter;
    double xforce, yforce;
};

class Actor : public GameObject, public fl::CollisionListener {
public:
    Actor(Game& g, fl::EntityWrapper e, fl::PhysicsOptions popt = fl::PhysicsOptions{}) : GameObject(g, e) {
        e.addPhysicsComponent(popt);
        e.addCollisionComponent({this});
    }
    virtual void CollisionInit (fl::EntityWrapper) {};
    virtual void CollisionDestroy (fl::EntityWrapper) {};
    virtual void collision(fl::EntityWrapper me, fl::EntityWrapper other, const fl::CollisionData&) {
        DEBUGLOG( other.getLogic<GameObject>()->toString(), " colliding with ",  me.getLogic<GameObject>()->toString(), '\n');
        this->bump(other.getLogic<Actor>());
    };
    virtual void bump(Actor* bumper) = 0;
    virtual void interact(Actor* actor) = 0;
    virtual void hit(const HitData &data) = 0;
};

#endif //FLATLAND_ACTOR_H

