//
// Created by cmarte on 6/10/15.
//

#include "Sword.h"
#include <Action.h>
#include "Player.h"

void Sword::hidesword(fl::EntityWrapper e) {
    Player* p = e.getLogic<Player>();
    Sword* s = dynamic_cast<Sword*>(p->getWeapon());
    if (s)
        e.removeSpriteComponent(s->sword);
    DEBUGLOG("Hiding sword sprite\n");
}

void Sword::use(Direction d) {
    if (isOut) return;
    isOut = true;
    fl::World& world = player().entity().world();
    /* create sword sprite */
    fl::SpriteOptions sopt("/home/cmarte/ClionProjects/flatland/Game/res/Sprites/sword.png", fl::Box{Level::TILESIZE, Level::TILESIZE});
    sopt.center = true;
    sopt.z = 5;
    sopt.rot = (d==Direction::UP)*90 + (d==Direction::LEFT)*180 + (d==Direction::DOWN)*270;
    sopt.offset.x = (double) Level::TILESIZE/2. * ((d==Direction::RIGHT) - (d==Direction::LEFT));
    sopt.offset.y = (double) Level::TILESIZE/2. * ((d==Direction::UP) - (d==Direction::DOWN));
    sword = player().entity().addSpriteComponent(sopt);
    /* queue sprite destroy */
    world.addEvent(player().entity(), hidesword, 100);
    /* queue cooldown reset */
    world.addEvent(player().entity(), cooldownOver, 101);
    /* Check if we hit someone */
    auto tr = player().entity().getTransform();
    fl::Rect r {tr.x + sopt.offset.x - sopt.box.w/2, tr.y + sopt.offset.y - sopt.box.h/2, sopt.box.w, sopt.box.h};
    std::vector<fl::Entity> cols = world.getPhysicsSystem().queryCollisions(r);
    for (auto _e : cols) {
        fl::EntityWrapper e {world, _e};
        Actor* a = e.getLogic<Actor>();
        if (a) a->hit(HitData{player(), player().strength() / 6. * ((d==Direction::RIGHT) - (d==Direction::LEFT)), player().strength() / 6. * ((d==Direction::UP) - (d==Direction::DOWN))});
    }
}

void Sword::hit(Actor *actor) {

}

Sword *Sword::Create(Player& player) {
    return new Sword(player);
}

void Sword::cooldownOver(fl::EntityWrapper e) {
    Player* p = e.getLogic<Player>();
    Sword* s = dynamic_cast<Sword*>(p->getWeapon());
    if (s)
        s->isOut = false;
    DEBUGLOG("coldown over\n");
}
