//
// Created by cmarte on 6/9/15.
//

#ifndef FLATLAND_WEAPON_H
#define FLATLAND_WEAPON_H

class Player;
class Actor;

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Weapon {
    Player& _player;
public:
    Weapon(Player& p) : _player(p) {}

    virtual Player& player() {return _player;}
    virtual void use(Direction) = 0;
    virtual void hit(Actor*) = 0;
    virtual void drop() = 0;
};


#endif //FLATLAND_WEAPON_H
