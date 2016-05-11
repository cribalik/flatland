//
// Created by cmarte on 6/6/15.
//

#ifndef FLATLAND_BALL_H
#define FLATLAND_BALL_H


#include "Actor.h"

class Ball : public Actor {

public:
    Ball(Game&);

    virtual void hit(const HitData &col);

    virtual void logicInit(fl::EntityWrapper) override;

    virtual void logicDestroy(fl::EntityWrapper) override;

    virtual void bump(Actor *bumper) override;

    virtual void interact(Actor *actor) override;

    virtual void activate() override;

    virtual void deactivate() override;

    virtual void deserialize(Game &game, std::istream &is) override;

    void serialize(Game &game, std::ostream &os);
};


#endif //FLATLAND_BALL_H
