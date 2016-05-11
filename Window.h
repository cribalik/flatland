/* 
 * File:   Window.h
 * Author: cmarte
 *
 * Created on December 8, 2014, 11:32 PM
 */

#ifndef FLATLAND_WINDOW_H
#define	FLATLAND_WINDOW_H

#include <SDL2/SDL_video.h>
#include "Renderer.h"
#include <SDL2/SDL_render.h>
#include <string>

namespace fl {

/* Simple wrapper for the SDL_Window object */
    class Window {
    public:
        explicit Window(
                std::string title = "",
                int w = 640,
                int h = 360,
                Uint32 flags = 0);
        Window(const Window& orig) = delete;
        Window(Window&&) noexcept;
        operator bool() {return ok;}
        operator SDL_Window*() {return raw_window;}
        virtual ~Window();
        SDL_Window* getSDLWindow() {return raw_window;}
        Renderer& getRenderer() {return renderer;}
        void show();
    private:
        SDL_Window* raw_window;
        Renderer renderer;
        bool ok;
    };

}
#endif	/* FLATLAND_WINDOW_H */
