//
// Created by cmarte on 5/26/15.
//

#ifndef FLATLAND_FL_SDLINIT_H
#define FLATLAND_FL_SDLINIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef FL_SDL_INIT_FLAGS
#define FL_SDL_INIT_FLAGS SDL_INIT_EVERYTHING
#endif

namespace fl {
    namespace detail {
        class _SDL_Initer {
            class Initsdl {
                Initsdl() { SDL_Init(FL_SDL_INIT_FLAGS); IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG); }
                ~Initsdl() { SDL_Quit(); }
            };
            /* static initialization will call constructor before anything else */
            static Initsdl initer;
        };
    }
}
#endif //FLATLAND_FL_SDLINIT_H
