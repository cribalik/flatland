//
// Created by cmarte on 5/30/15.
//

#ifndef FLATLAND_INPUTCOMPONENT_H
#define FLATLAND_INPUTCOMPONENT_H

#include <SDL_joystick.h>
#include <exception>
#include "System.h"

namespace fl {

    enum class Button : unsigned int {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
        A = 4,
        B = 5,
        X = 6,
        Y = 7,
        START = 8,
        SELECT = 9
    };

    DEFINE_COMPONENT_HANDLE(Input) SDL_JoystickID;

    class NoFreeControllersException : public std::exception {
        virtual const char* what() const noexcept override {return "There are no more free controllers";}
    };

    class InputHandler;

    struct InputOptions {
        enum Which {NONE, KEYBOARD, FIRST_FREE_CONTROLLER, FIRST_FREE};
        InputHandler* handler;
        Which which;
        InputHandle controller;
        InputOptions(Which which, InputHandler* handler) : handler(handler), which(which) {}
        InputOptions(InputHandle controller, InputHandler* handler) : handler(handler), which(NONE), controller(controller) {}
    };

}
#endif //FLATLAND_INPUTCOMPONENT_H
