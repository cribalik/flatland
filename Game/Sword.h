//
// Created by cmarte on 6/10/15.
//

#ifndef FLATLAND_SWORD_H
#define FLATLAND_SWORD_H


#include <SpriteComponent.h>
#include <EntityWrapper.h>
#include "Weapon.h"

class Sword : public Weapon {

    fl::SpriteHandle sword;
    bool isOut = false;
    Sword(Player &p) : Weapon(p) {}

public:

    virtual void use(Direction direction) override;

    virtual void hit(Actor *actor) override;

    virtual void drop() override {delete this;};

    static Sword* Create(Player&);
private:
    static void hidesword(fl::EntityWrapper);
    static void cooldownOver(fl::EntityWrapper);
};


#endif //FLATLAND_SWORD_H
