//
// Created by cmarte on 6/6/15.
//

#include "Ball.h"
#include "Game.h"

void Ball::hit(const HitData &col) {

}

Ball::Ball(Game& g) : Actor(g, g.getWorld().createEntity(static_cast<fl::Tag>(GameObjectID::Ball), fl::Transform{}, this)) {

}

void Ball::bump(Actor *bumper) {
    DEBUGLOG(this->toString(), " bumped into " , bumper->toString(), "!\n");
}

void Ball::interact(Actor *actor) {

}

void Ball::activate() {

}

void Ball::deactivate() {

}

void Ball::deserialize(Game &game, std::istream &is) {
    GameObject::deserialize( game, is);
}

void Ball::serialize(Game &game, std::ostream &os) {
    GameObject::serialize(game, os);
}

void Ball::logicDestroy(fl::EntityWrapper wrapper) {

}

void Ball::logicInit(fl::EntityWrapper wrapper) {

}
