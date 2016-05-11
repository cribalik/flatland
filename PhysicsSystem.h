//
// Created by cmarte on 5/26/15.
//

#ifndef FLATLAND_PHYSICSSYSTEM_H
#define FLATLAND_PHYSICSSYSTEM_H

#include "System.h"
#include "Geometry.h"
#include "Utility/Table.h"
#include "Utility/ContiguousMap.h"
#include "PhysicsComponent.h"
#include "Core.h"

namespace fl {

    struct Wall {
       double x,y,w,h;
    };

    class PhysicsSystem {

        struct Data {
            double vx,vy;
            Point offset;
            double gravity;
            double bounce;
            Box hitbox;
            double friction;
            double drag;
        };

        ContiguousMap<Data, Entity> _data;
        std::vector<Wall> _walls;
        double _g = 9.82;

    public:

        DECLARE_SYSTEM_METHODS_DEFAULT_HANDLE(Physics)

        void applyImpulse(Entity e, double x, double y) {_data[e].vx += x; _data[e].vy += y;}
        std::vector<Entity> queryCollisions(const fl::Rect& r);
        void addWall(Wall);
        void setG(double g) {_g = g;};
        const double& getG() const {return _g;}
        Vel getVelocity(Entity e) {const auto& v = _data[e]; return {v.vx, v.vy};}
        void setVelocity(Entity e, Vel vel) {auto& v = _data[e]; v.vx = vel.vx; v.vy = vel.vy;}

    private:
        Data getData(Entity e) {return _data[e];}
        void setData(Entity e, const Data& d) {_data[e] = d;}
        friend class CollisionSystem;
    };

}

#endif //FLATLAND_PHYSICSSYSTEM_H
