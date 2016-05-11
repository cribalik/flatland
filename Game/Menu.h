//
// Created by cmarte on 5/31/15.
//

#ifndef FLATLAND_MENU_H
#define FLATLAND_MENU_H

#include <World.h>
#include "GameObject.h"
#include <Core.h>

class Game;

class Menu : public GameObject {

public:
    virtual void activate() override {FL_STUB;}

    virtual void deactivate() override {}

    virtual void logicInit(fl::EntityWrapper wrapper) override {};

    virtual void logicDestroy(fl::EntityWrapper wrapper) override {delete this;};


    using Handle = fl::EntityWrapper;

    static Menu* Create(Game& game);
    static Menu* Create(Game& game, std::istream&) {return Create(game);}

private:
/* Private constructor. Use Menu::Create to create */
    Menu(Game& g, const fl::EntityWrapper &entity) : GameObject(g, entity) {}

    static void newGame(fl::EntityWrapper e);

};


#endif //FLATLAND_MENU_H
