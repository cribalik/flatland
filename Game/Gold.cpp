//
// Created by cmarte on 6/8/15.
//

#include "Gold.h"
#include "Game.h"
#include "Level.h"
#include "Player.h"

void Gold::bump(Actor *bumper) {
    if (bumper->type() == GameObjectID::Player) {
        static_cast<Player *>(bumper)->giveMoney(_amount);
        entity().destroy();
    }
}

void Gold::interact(Actor *actor) {

}

void Gold::hit(const HitData& hit) {
    entity().world().getPhysicsSystem().applyImpulse(entity(), hit.xforce, hit.yforce);
    DEBUGLOG("Gold was hit\n");
}

void Gold::activate() {
    entity().addSpriteComponent(fl::SpriteOptions(
            "/home/cmarte/ClionProjects/flatland/Game/res/Sprites/gold.png",
            fl::Box{Level::TILESIZE, Level::TILESIZE},
            fl::Point{},
            5
    ));
    fl::PhysicsOptions popt;
    popt.hitbox = fl::Box{Level::TILESIZE, Level::TILESIZE};
    popt.center = true;
    popt.drag = 0.001;
    entity().addPhysicsComponent(popt);
}

void Gold::deactivate() {
    DEBUGLOG_AND_DIE("Not implemented!\n");
}

void Gold::serialize(Game &game, std::ostream &os) {
    Actor::serialize(game, os);
    os << _amount << ' ' << _pos.x << ' ' << _pos.y << '\n';
}

void Gold::deserialize(Game &game, std::istream &is) {
    Actor::deserialize(game, is);
}

void Gold::logicInit(fl::EntityWrapper wrapper) {

}

void Gold::logicDestroy(fl::EntityWrapper wrapper) {
    delete this;
}

Gold *Gold::Create(Game &game, unsigned int amount, fl::Point pos) {
    auto e = game.getWorld().createEntity(static_cast<fl::Tag>(GameObjectID::Gold), {pos.x, pos.y});
    Gold* gold = new Gold(game, e);
    gold->_amount = amount;
    gold->_pos = pos;
    return gold;
}

Gold *Gold::Create(Game &game, std::istream &is) {
    unsigned int amount;
    fl::Point pos;
    is >> amount >> pos.x >> pos.y;
    return Create(game, amount, pos);
}
