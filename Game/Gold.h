//
// Created by cmarte on 6/8/15.
//

#ifndef FLATLAND_GOLD_H
#define FLATLAND_GOLD_H


#include "Actor.h"

class Gold : public Actor {

    unsigned int _amount;
    fl::Point _pos;

    Gold(Game &g, const fl::EntityWrapper &e) : Actor(g, e) {}

public:

    virtual void bump(Actor *bumper) override;

    virtual void interact(Actor *actor) override;

    virtual void hit(const HitData &col) override;

    virtual void activate() override;

    virtual void deactivate() override;

    virtual void serialize(Game &game, std::ostream &os) override;

    virtual void deserialize(Game &game1, std::istream &is) override;

    virtual void logicInit(fl::EntityWrapper wrapper) override;

    virtual void logicDestroy(fl::EntityWrapper wrapper) override;

    static Gold* Create(Game&, unsigned int amount, fl::Point pos);
    static Gold* Create(Game&, std::istream&);
};


#endif //FLATLAND_GOLD_H
