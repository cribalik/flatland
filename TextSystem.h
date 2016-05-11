//
// Created by cmarte on 5/31/15.
//

#ifndef FLATLAND_TEXTSYSTEM_H
#define FLATLAND_TEXTSYSTEM_H

#include <SDL_render.h>
#include <Utility/ContiguousMultiMap.h>
#include "System.h"
#include "TextComponent.h"
#include "SpriteComponent.h"
#include <memory>
#include <SDL2/SDL_ttf.h>
#include <map>

namespace fl {

    /* Uses Spritesystem as its rendering engine. */

    class TextSystem {

        static const int FONT_POINTS = 20;

        std::map<Font, TTF_Font*> _fonts;

    public:

        DECLARE_SYSTEM_METHODS(Text)

        /* Load fonts from a list of paths. May only be done once!
         * The fonts that can then be referenced by zero-based index
         * in order of input */
        void loadFonts(const std::vector<std::string>& paths);

        ~TextSystem();

    private:

        void _processTextOptions(const TextOptions&, SpriteOptions&, SDL_Texture*&);
        SDL_Texture* _loadTexture(const std::string& str, TTF_Font* font, const SDL_Color& color, unsigned int width);


    };

}

#endif //FLATLAND_TEXTSYSTEM_H
