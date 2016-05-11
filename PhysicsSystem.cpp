//
// Created by cmarte on 5/26/15.
//

#include "PhysicsSystem.h"
#include "World.h"
#include <algorithm>

// #define FL_DRAW_WALLS

namespace fl {

    PhysicsSystem::PhysicsSystem(World &w) : _world(w)
    {}

    PhysicsHandle PhysicsSystem::addComponent(Entity e, const PhysicsOptions & opt) {
        Data d {
                opt.vx,
                opt.vy,
                opt.offset,
                opt.gravity,
                opt.bounce,
                opt.hitbox,
                opt.friction,
                opt.drag
        };
        if (opt.center) {
            d.offset.x = d.hitbox.w/2.;
            d.offset.y = d.hitbox.h/2.;
        }
        _data.insert(e, d);
    }

    PhysicsHandle PhysicsSystem::addComponent(Entity e, PhysicsOptions && opt) {
        this->addComponent(e, opt);
    }

    void PhysicsSystem::removeEntity(Entity e) {
        _data.erase(e);
    }

    void PhysicsSystem::update(Time dt) {
        for (auto& p : _data) {
            auto tr = _world.getTransform(p.first);
            auto& d = p.second;

            /* Gravity */
            d.vy += _g * d.gravity;
            /* Drag */
            d.vx = d.vx > 0 ? d.vx - std::min(d.drag*dt, d.vx) : d.vx - std::max(-d.drag*dt, d.vx);
            d.vy = d.vy > 0 ? d.vy - std::min(d.drag*dt, d.vy) : d.vy - std::max(-d.drag*dt, d.vy);
            /* TODO: friction */

            tr.x -= d.offset.x;
            tr.y -= d.offset.y;
            auto r = tr.x + d.hitbox.w;
            auto b = tr.y + d.hitbox.h;
            auto dx = d.vx * dt;
            auto dy = d.vy * dt;
            /* Walls FIXME: something wrong TODO: Optimize */
            for (const Wall& w : _walls) {
                #ifdef FL_DRAW_WALLS
                {SDL_SetRenderDrawColor(_world.getRenderer(), 100,255,100,255);
                SDL_Rect r {tr.x, tr.y, d.hitbox.w, d.hitbox.h};
                SDL_RenderFillRect(_world.getRenderer(), &r);}
                #endif
                /* From sides */
                if ( (b + std::max(0.,dy) > w.y) && (tr.y + std::min(0.,dy) < w.y + w.h) ) {
                    if ((r <= w.x) && (r + dx >= w.x))
//                        dx = w.x - r;
                        dx = 0;
                    else if ((tr.x >= w.x + w.w) && (tr.x + dx <= w.x + w.w))
//                        dx = w.x + w.w - tr.x;
                        dx = 0;
                }

                /* From above and below */
                if ((r + std::max(0.,dx) > w.x) && (tr.x + std::min(0.,dx) < w.x + w.w) ) {
                    if (b <= w.y && b + dy >= w.y)
//                        dy = w.y - b;
                        dy = 0;
                    else if (tr.y >= w.y + w.h && tr.y + dy <= w.y + w.h)
//                        dy = w.y + w.h - tr.y;
                        dy = 0;
                }
            };

            auto& tr_ref = _world.getTransform(p.first);
            d.vx = dx/dt;
            d.vy = dy/dt;
            tr_ref.x += dx;
            tr_ref.y += dy;
        }
        #ifdef FL_DRAW_WALLS
        SDL_SetRenderDrawColor(_world.getRenderer(), 255, 255, 0, 255);
        for (const Wall& w : _walls) {
            SDL_Rect r {(int) w.x,(int) w.y,(int) w.w,(int) w.h};
            SDL_RenderFillRect(_world.getRenderer(), &r);
        }
        #endif

    }

    void PhysicsSystem::addWall(Wall wall) {
        _walls.push_back(wall);
    }

    std::vector<Entity> PhysicsSystem::queryCollisions(const fl::Rect &r) {
        std::vector<Entity> res;
        for (auto& p : _data) {
            auto tr = _world.getTransform(p.first);
            auto le = tr.x - p.second.offset.x;
            auto ri = le + p.second.hitbox.w;
            auto to = tr.y - p.second.offset.y;
            auto bo = to + p.second.hitbox.h;
            if (!(r.x+r.w < le || r.x > ri || r.y > bo || r.y+r.h < to))
                res.push_back(p.first);
            // #ifdef FL_DRAW_WALLS
            SDL_SetRenderDrawColor(_world.getRenderer(), 0, 255, 0, 255);
            SDL_Rect r {(int) le,(int) to,(int) p.second.hitbox.w,(int) p.second.hitbox.h};
            SDL_RenderFillRect(_world.getRenderer(), &r);
            // #endif
        }
        SDL_SetRenderDrawColor(_world.getRenderer(), 255,0,0,255);
        SDL_Rect rtmp {r.x, r.y, r.w, r.h};
        SDL_RenderFillRect(_world.getRenderer(), &rtmp);
        return res;
    }
}