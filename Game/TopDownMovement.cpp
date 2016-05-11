//
// Created by cmarte on 6/9/15.
//

#include "TopDownMovement.h"
#include "World.h"

void TopDownMovement::init(fl::EntityWrapper wrapper, fl::InputHandle handle) {

}

void TopDownMovement::buttonDown(fl::EntityWrapper e, fl::InputHandle , fl::Button b) {
        e.world().getPhysicsSystem().applyImpulse(e,
             0.5*((b == fl::Button::RIGHT) - (b == fl::Button::LEFT)),
             0.5*((b == fl::Button::DOWN) - (b == fl::Button::UP))
        );
}

void TopDownMovement::buttonUp(fl::EntityWrapper wrapper, fl::InputHandle handle, fl::Button button) {

}

void TopDownMovement::destroy(fl::EntityWrapper wrapper, fl::InputHandle handle) {
    delete this;
}

TopDownMovement *TopDownMovement::Create() {
    return new TopDownMovement;
}
