/* 
 * File:   Window.cpp
 * Author: cmarte
 * 
 * Created on December 8, 2014, 11:32 PM
 */

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include "Window.h"
#include "Renderer.h"

namespace fl {

    Window::Window(
            std::string title,
            int w,
            int h,
            Uint32 flags)
    {
        this->ok = static_cast<bool>(SDL_CreateWindowAndRenderer(w, h, flags, &this->raw_window, &this->renderer.r));
    }

    Window::Window(Window&& w) noexcept : raw_window(std::move(w.raw_window)), renderer(std::move(w.renderer))
    {
        w.raw_window = nullptr;
    }

    void Window::show()
    {
        SDL_ShowWindow(this->raw_window);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(this->raw_window);
        SDL_DestroyRenderer(this->renderer.getSDLRenderer());
    }


}