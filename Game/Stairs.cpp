//
// Created by cmarte on 6/8/15.
//

#include "Stairs.h"
#include "Game.h"
#include "Level.h"

void Stairs::bump(Actor *bumper) {

}

void Stairs::interact(Actor *actor) {

}

void Stairs::hit(const HitData &col) {

}

void Stairs::activate() {
    entity().addSpriteComponent(fl::SpriteOptions(
            "/home/cmarte/ClionProjects/flatland/Game/res/Sprites/stairs.png",
            fl::Box{Level::TILESIZE, Level::TILESIZE},
            _pos
    ));
}

void Stairs::deactivate() {

}

Stairs *Stairs::Create(Game &game, fl::Point pos) {
    Stairs* stairs = new Stairs(game, game.getWorld().createEntity(static_cast<fl::Tag>(GameObjectID::Stairs)), pos);
    return stairs;
}

Stairs *Stairs::Create(Game &game, std::istream& is) {
    fl::Point p;
    is >> p.x >> p.y;
    return Create(game, p);
}

void Stairs::serialize(Game &game, std::ostream &os) {
    Actor::serialize(game, os);
    os << _pos.x << ' ' << _pos.y << '\n';
}
