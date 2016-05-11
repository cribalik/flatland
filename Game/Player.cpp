//
// Created by cmarte on 6/9/15.
//

#include "Player.h"
#include "Game.h"
#include "TopDownMovement.h"

class PlayerMovement : public fl::InputHandler, public fl::Updatable {
    int refcount = 0;
    double ACC = 0.01;
    double MAX_SPEED = 0.3;
    fl::InputHandle inputdevice = fl::InputSystem::KEYBOARD;

public:
    virtual void init(fl::EntityWrapper wrapper, fl::InputHandle handle) {++refcount;}

    virtual void buttonDown(fl::EntityWrapper wrapper, fl::InputHandle handle, fl::Button button);

    virtual void buttonUp(fl::EntityWrapper wrapper, fl::InputHandle handle, fl::Button button);

    virtual void destroy(fl::EntityWrapper wrapper, fl::InputHandle handle) {--refcount; if (!refcount) delete this;};

    virtual void updateInit(fl::EntityWrapper wrapper) {++refcount;};

    virtual void updateDestroy(fl::EntityWrapper wrapper) {--refcount; if (!refcount) delete this;};

    virtual void update(fl::EntityWrapper wrapper, fl::Time time1);

    static PlayerMovement* Create(Game&, Player& player, fl::InputOptions::Which which = fl::InputOptions::KEYBOARD, double RUN_SPEED = 0.5)
    {
        PlayerMovement* p = new PlayerMovement;
        p->inputdevice = player.entity().addInputComponent(fl::InputOptions(which, p));
        player.entity().addUpdateListener(p);
        return p;
    }
};

void Player::bump(Actor *bumper) {

}

void Player::interact(Actor *actor) {

}

void Player::hit(const HitData &col) {

}

void Player::activate() {
    DEBUGLOG("Player activated!\n");
    PlayerMovement::Create(game(), *this, fl::InputOptions::KEYBOARD, RUN_SPEED);
    fl::PhysicsOptions popt;
//    popt.hitbox = fl::Box{Level::TILESIZE*0.5, Level::TILESIZE*0.5};
    popt.hitbox = {10,10};
    popt.friction = 0;
    popt.vx = 2;
    popt.center = true;
    entity().addPhysicsComponent(popt);
    fl::SpriteOptions sopt("/home/cmarte/ClionProjects/flatland/Game/res/Sprites/gold.png");
    sopt.z = 20;
//    sopt.box = {Level::TILESIZE,Level::TILESIZE};
    sopt.box = {10,10};
    sopt.autosize = false;
    sopt.center = true;
    entity().addSpriteComponent(sopt);
}

void Player::deactivate() {
    DEBUGLOG_AND_DIE("Not implemented\n");
}

void Player::serialize(Game &game, std::ostream &os) {
    GameObject::serialize(game, os);
}

void Player::deserialize(Game &game, std::istream &is) {
    GameObject::deserialize(game, is);
}

void PlayerMovement::buttonDown(fl::EntityWrapper e, fl::InputHandle , fl::Button b) {
    Direction d;
    switch (b) {
        case fl::Button::A: d = Direction::DOWN; break;
        case fl::Button::B: d = Direction::RIGHT; break;
        case fl::Button::X: d = Direction::LEFT; break;
        case fl::Button::Y: d = Direction::UP; break;
        default: return;
    }
    Weapon* w = e.getLogic<Player>()->getWeapon();
    if (w) w->use(d);
}

void PlayerMovement::buttonUp(fl::EntityWrapper , fl::InputHandle handle, fl::Button button) {

}

Player *Player::Create(Game &game, fl::Point pos) {
    auto e = game.getWorld().createEntity(static_cast<fl::Tag>(GameObjectID::Player), {pos.x, pos.y});
    return new Player(game, e);
}

void PlayerMovement::update(fl::EntityWrapper e, fl::Time dt) {
    fl::InputSystem& is = e.world().getInputSystem();
    int xdir = (is.isDown(inputdevice, fl::Button::RIGHT) - is.isDown(inputdevice, fl::Button::LEFT));
    int ydir = (is.isDown(inputdevice, fl::Button::DOWN) - is.isDown(inputdevice, fl::Button::UP));

    fl::Vel v = e.world().getPhysicsSystem().getVelocity(e);
    if (xdir == 0)
        v.vx *= pow(0.5,dt/14.);
    else
        v.vx = std::max(std::min(MAX_SPEED, v.vx + xdir*ACC*dt), -MAX_SPEED);
    if (ydir == 0)
        v.vy *= pow(0.5,dt/14.);
    else
        v.vy = std::max(std::min(MAX_SPEED, v.vy + ydir*ACC*dt), -MAX_SPEED);
    e.world().getPhysicsSystem().setVelocity(e, v);

}
