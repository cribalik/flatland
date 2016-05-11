//
// Created by cmarte on 5/31/15.
//

#ifndef FLATLAND_GAME_H
#define FLATLAND_GAME_H

#define FL_DRAW_WALLS
#include <World.h>
#include <Window.h>
#include "Menu.h"
#include "Level.h"
#include "Camera.h"

class Game {

    fl::Window window;
    fl::World world;
    Level* _level = nullptr;
    Camera* camera = nullptr;

public:

    Game() : window("Game", 800, 550, SDL_WINDOW_RESIZABLE), world(window) {}

    fl::World& getWorld() {return world;}

    void startLevel(Level*);

    void setCameraOn(fl::EntityWrapper);

    void run();

};


#endif //FLATLAND_GAME_H
