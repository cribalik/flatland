//
// Created by cmarte on 6/8/15.
//

#ifndef FLATLAND_STAIRS_H
#define FLATLAND_STAIRS_H

#include "Actor.h"

class Stairs : public Actor {

    fl::Point _pos;

    Stairs(Game &g, const fl::EntityWrapper &e, fl::Point pos) : Actor(g, e), _pos(pos) { }

public:
    virtual void bump(Actor *bumper) override;

    virtual void interact(Actor *actor) override;

    virtual void hit(const HitData &col) override;

    virtual void activate() override;

    virtual void deactivate() override;

    virtual void logicInit(fl::EntityWrapper wrapper) override {};

    virtual void logicDestroy(fl::EntityWrapper wrapper) override {delete this;};

    virtual void serialize(Game&, std::ostream&) override;

    static Stairs* Create(Game&, fl::Point pos = {});
    static Stairs* Create(Game&, std::istream&);
};


#endif //FLATLAND_STAIRS_H
