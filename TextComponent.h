//
// Created by cmarte on 5/31/15.
//

#ifndef FLATLAND_TEXTCOMPONENT_H
#define FLATLAND_TEXTCOMPONENT_H

#include <SDL_pixels.h>
#include "Geometry.h"
#include <string>
#include <limits.h>

namespace fl {

    typedef SDL_Color Color;

    typedef std::size_t Font;

    DEFINE_COMPONENT_OPTIONS(Text)
    struct TextOptions {
        std::string text;
        Font font = 0;
        Color color = {255,255,255,255};
        unsigned int width = 1920;
        Point offset = {0., 0.};
        enum Align {LEFT, RIGHT, CENTER};
        Align align = CENTER;
        bool vcenter = true;
        unsigned int z = UINT_MAX;
        double textsize = 50; /* average height in pixels */
        TextOptions() {}
        TextOptions(const std::string& text) : text(text) {}
        TextOptions(const std::string& text, unsigned int width) : text(text), width(width) {}
        TextOptions(const std::string& text, Point offset) : text(text), offset(offset) {}
        TextOptions(const std::string& text, unsigned int width, Point offset) : text(text), width(width), offset(offset) {}
    };

    DEFINE_COMPONENT_HANDLE(Text) ID;

}

#endif //FLATLAND_TEXTCOMPONENT_H
