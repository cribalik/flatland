//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_INPUTSYSTEM_H
#define FLATLAND_INPUTSYSTEM_H

#include "System.h"
#include <map>
#include <set>
#include <SDL_gamecontroller.h>
#include <SDL_keyboard.h>
#include <exception>
#include "InputComponent.h"
#include "Core.h"
#include "EntityWrapper.h"

namespace fl {

    class InputHandler {
    public:
        virtual void init(EntityWrapper, InputHandle) = 0;
        virtual void buttonDown(EntityWrapper, InputHandle, Button) = 0;
        virtual void buttonUp(EntityWrapper, InputHandle, Button) = 0;
        virtual void destroy(EntityWrapper, InputHandle) = 0;
    };

    class InputSystem {


        static std::map<std::pair<InputHandle, Button>, bool> _isDown;
        std::map<Entity, InputHandler*> _keyboardListeners;
        std::map<InputHandle, std::map<Entity, InputHandler*>> _controllerListeners;
        std::set<InputHandle> _free;
        std::map<SDL_Keycode, Button> _keyMap;
        std::map<SDL_GameControllerButton, Button> _buttonMap;

    public:

        constexpr static const InputHandle KEYBOARD = -1;

        bool isDown(InputHandle i, Button b) {return _isDown[{i,b}];};

        DECLARE_SYSTEM_METHODS(Input)

    private:

        void _findControllers();

    };

}

#endif //FLATLAND_INPUTSYSTEM_H
