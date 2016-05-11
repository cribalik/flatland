//
// Created by cmarte on 5/30/15.
//

#ifndef FLATLAND_SPRITECOMPONENT_H
#define FLATLAND_SPRITECOMPONENT_H

#include "System.h"
#include "Geometry.h"
#include <string>
#include "Core.h"


namespace fl {

    DEFINE_COMPONENT_OPTIONS(Sprite)
    struct SpriteOptions {
        std::string imagePath;
        Box box = {0,0};
        Point offset = {0,0};
        unsigned int z = 100;
        double rot = 0; /* Rotation in degrees */
        /* TODO: Implement src rect */
        bool center = true;
        bool autosize = true;
        SpriteOptions() {}
        SpriteOptions(const std::string& imagePath, Box box, Point offset = {0,0}, unsigned int z = 0) : imagePath(imagePath), box(box), offset(offset), autosize(false), z(z) {}
        SpriteOptions(const std::string& imagePath, Point offset = {0,0}, unsigned int z = 0) : imagePath(imagePath), offset(offset), z(z) {}
    };

    DEFINE_COMPONENT_HANDLE(Sprite) ID;

}

#endif //FLATLAND_SPRITECOMPONENT_H
