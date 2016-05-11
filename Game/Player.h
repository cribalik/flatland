//
// Created by cmarte on 6/9/15.
//

#ifndef FLATLAND_PLAYER_H
#define FLATLAND_PLAYER_H


#include "Actor.h"
#include "Level.h"
#include "Sword.h"

class Player : public Actor {
    constexpr const static double RUN_SPEED = Level::TILESIZE/100.;
    int refcount = 0;
    Weapon* weapon;
    Player(Game &g, const fl::EntityWrapper &e) : Actor(g, e), weapon(Sword::Create(*this)) { }
    int _strength = 3;
    int _money = 0;

public:

    virtual void bump(Actor *bumper) override;

    void giveMoney(int m) {_money += m;}

    int& strength() {return _strength;}

    Weapon* getWeapon() {return weapon;}

    virtual void interact(Actor *actor) override;

    virtual void hit(const HitData &col) override;

    virtual void activate() override;

    virtual void deactivate() override;

    virtual void serialize(Game &game, std::ostream &os) override;

    virtual void deserialize(Game &game1, std::istream &is) override;

    virtual void logicInit(fl::EntityWrapper wrapper) override {++refcount;};

    virtual void logicDestroy(fl::EntityWrapper wrapper) override {++refcount; if (!refcount) delete this;};

    static Player* Create(Game&, fl::Point pos);

};


#endif //FLATLAND_PLAYER_H
