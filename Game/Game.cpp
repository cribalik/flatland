//
// Created by cmarte on 5/31/15.
//

#include "Game.h"
#include "TopDownMovement.h"

void Game::run() {
    world.setFPS(60);
    world.getTextSystem().loadFonts({"/home/cmarte/ClionProjects/flatland/Game/res/Fonts/Capture_it.ttf"});
//    Menu::Create(*this);
    startLevel(Level::Create(*this, "/home/cmarte/ClionProjects/flatland/Game/res/Levels/level1.lv"));
//    world.getPhysicsSystem().addWall({300,300,300,300});
//
//    auto e = world.createEntity(0, {100,100});
//
//    e.addInputComponent(fl::InputOptions(fl::InputOptions::KEYBOARD, TopDownMovement::Create()));
//
//    fl::PhysicsOptions popt;
//    popt.hitbox = {100,100};
//    popt.center = true;
//    e.addPhysicsComponent(popt);
    world.run();
}

void Game::setCameraOn(fl::EntityWrapper target) {
    if (!camera) {
        camera = Camera::Create(*this, target, 15*Level::TILESIZE, (15*Level::TILESIZE*1080)/1920);
        camera->activate();
    }
    camera->setTarget(target);
}

void Game::startLevel(Level *level) {
    if (_level) _level->entity().destroy();
    _level = level;
    level->activate();
}
