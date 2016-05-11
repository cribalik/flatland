//
// Created by cmarte on 5/27/15.
//

#include <SDL_events.h>
#include "InputSystem.h"

namespace fl {

    constexpr const InputHandle InputSystem::KEYBOARD;
    std::map<std::pair<InputHandle, Button>, bool> InputSystem::_isDown;

    InputSystem::InputSystem(World &w) : _world(w)
    , _keyMap{
            {SDLK_w,      Button::UP},
            {SDLK_s,      Button::DOWN},
            {SDLK_a,      Button::LEFT},
            {SDLK_d,      Button::RIGHT},
            {SDLK_i,      Button::A},
            {SDLK_o,      Button::B},
            {SDLK_u,      Button::X},
            {SDLK_y,      Button::Y},
            {SDLK_RETURN, Button::START},
            {SDLK_RSHIFT, Button::SELECT}
    }
    , _buttonMap {
            {SDL_CONTROLLER_BUTTON_DPAD_UP, Button::UP},
            {SDL_CONTROLLER_BUTTON_DPAD_DOWN, Button::DOWN},
            {SDL_CONTROLLER_BUTTON_DPAD_LEFT, Button::LEFT},
            {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, Button::RIGHT},
            {SDL_CONTROLLER_BUTTON_A, Button::A},
            {SDL_CONTROLLER_BUTTON_B, Button::B},
            {SDL_CONTROLLER_BUTTON_X, Button::X},
            {SDL_CONTROLLER_BUTTON_Y, Button::Y},
            {SDL_CONTROLLER_BUTTON_START, Button::START},
            {SDL_CONTROLLER_BUTTON_BACK, Button::SELECT}
    }
    {
        this->_findControllers();
    }

    void InputSystem::update(Time dt) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        exit(0);

                case SDL_KEYDOWN: {
                    auto button_it = _keyMap.find(event.key.keysym.sym);
                    if (button_it == _keyMap.end()) break;
                    Button button = button_it->second;
                    _isDown[{KEYBOARD,button}] = true;
                    for (auto& p : _keyboardListeners)
                        p.second->buttonDown({_world, p.first}, KEYBOARD, button);
                    break;
                };

                case SDL_KEYUP: {
                    auto button_it = _keyMap.find(event.key.keysym.sym);
                    if (button_it == _keyMap.end()) break;
                    Button button = button_it->second;
                    _isDown[{KEYBOARD,button}] = false;
                    for (auto& p : _keyboardListeners)
                        p.second->buttonUp({_world, p.first}, KEYBOARD, button);
                    break;
                };

                case SDL_JOYBUTTONDOWN: {
                    auto button_it = _buttonMap.find(static_cast<SDL_GameControllerButton>(event.cbutton.button));
                    if (button_it == _buttonMap.end()) break;
                    Button button = button_it->second;
                    _isDown[{event.cbutton.which, button}] = true;
                    auto l = _controllerListeners.find(event.cbutton.which);
                    if (l == _controllerListeners.end()) break;
                    for (auto& p : l->second)
                        p.second->buttonDown({_world, p.first}, l->first, button);
                    break;
                };

                case SDL_JOYBUTTONUP: {
                    auto button_it = _buttonMap.find(static_cast<SDL_GameControllerButton>(event.cbutton.button));
                    if (button_it == _buttonMap.end()) break;
                    Button button = button_it->second;
                    _isDown[{event.cbutton.which, button}] = false;
                    auto l = _controllerListeners.find(event.cbutton.which);
                    if (l == _controllerListeners.end()) break;
                    for (auto& p : l->second)
                        p.second->buttonUp({_world, p.first}, l->first, button);
                    break;
                };
            }
        }
    }

    InputHandle InputSystem::addComponent(Entity e, const InputOptions & opt) {

        InputHandle ret;

        if (opt.which != InputOptions::NONE) {

            switch (opt.which) {

                case InputOptions::FIRST_FREE: {
                    if (_free.empty())
                        throw NoFreeControllersException();
                    auto controller = _free.begin();
                    if (*controller == KEYBOARD)
                        _keyboardListeners.insert({e, opt.handler});
                    else
                        _controllerListeners[*controller].insert({e, opt.handler});
                    _free.erase(controller);
                    ret = *controller;
                } break;

                case InputOptions::FIRST_FREE_CONTROLLER: {
                    if (_free.empty() || (*_free.begin() == KEYBOARD && _free.size() == 1))
                        throw NoFreeControllersException();
                    auto controller = _free.begin();
                    if (*controller == KEYBOARD) ++controller;
                    _controllerListeners[*controller].insert({e, opt.handler});
                    _free.erase(controller);
                    ret = *controller;
                } break;

                case InputOptions::KEYBOARD: {
                    _keyboardListeners.insert({e, opt.handler});
                    ret = KEYBOARD;
                } break;
            }
        }
        else {
            if (opt.controller == KEYBOARD)
                _keyboardListeners.insert({e, opt.handler});
            else
                _controllerListeners[opt.controller].insert({e, opt.handler});
            ret = opt.controller;
        }

        opt.handler->init({_world, e}, ret);

        return ret;
    }

    InputHandle InputSystem::addComponent(Entity e, InputOptions && opt) {
        this->addComponent(e, opt);
    }

    void InputSystem::removeEntity(Entity e) {

        auto it = _keyboardListeners.find(e);
        if (it != _keyboardListeners.end()) {
            it->second->destroy({_world, e}, KEYBOARD);
            _keyboardListeners.erase(it);
        }

        for (auto& map : _controllerListeners) {
            auto it = map.second.find(e);
            if (it != map.second.end()) {
                it->second->destroy({_world, e}, map.first);
                map.second.erase(it);
            }
        }
    }

    void InputSystem::removeComponent(Entity e, InputHandle handle) {

        if (handle == KEYBOARD) {
            auto it = _keyboardListeners.find(e);
            if (it == _keyboardListeners.end()) return;
            it->second->destroy({_world, e}, KEYBOARD);
            _keyboardListeners.erase(it);
        }

        else {
            auto it = _controllerListeners.find(handle);
            if (it == _controllerListeners.end()) return;
            auto cit = it->second.find(e);
            if (cit == it->second.end()) return;
            cit->second->destroy({_world, e}, it->first);
            it->second.erase(cit);
        }
    }

    void InputSystem::_findControllers() {
//        _free.insert(KEYBOARD);
        _free.insert(KEYBOARD);
        for (int i = 0, lim = SDL_NumJoysticks(); i < lim; ++i) {
            if (SDL_IsGameController(i)
                && _controllerListeners.count(i) == 0
                && _free.count(i) == 0)
            {
                SDL_GameControllerOpen(i);
                _free.insert(i);
            }
        }
    }

    InputOptions InputSystem::getOptions(Entity e, InputHandle handle) {
        FL_STUB;
    }

    void InputSystem::setOptions(Entity e, InputHandle handle, const InputOptions &opt) {
        FL_STUB;
    }

}