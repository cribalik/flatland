//
// Created by cmarte on 5/26/15.
//

#ifndef FLATLAND_SPRITESYSTEM_H
#define FLATLAND_SPRITESYSTEM_H

#include <SDL_render.h>
#include "System.h"
#include "Utility/ContiguousMultiMap.h"
#include "SpriteComponent.h"

namespace fl {

    class SpriteSystem {

        /* TODO: Use openGL instead of SDL's rendering. */

        struct Data {
            ID id;
            SDL_Texture* texture;
            unsigned int z;
            double rot;
            double w,h;
            double xoffset, yoffset;
            double xalign, yalign;
        };

        ContiguousMultiMap<Data, Entity> _data;

    public:

        DECLARE_SYSTEM_METHODS(Sprite);

    private:

        SDL_Texture* _loadCachedTexture(const std::string& path);
        static SDL_Texture* _loadTexture(const char* path, SDL_Renderer*, int* h = nullptr, int* w = nullptr);
        ContiguousMultiMap<Data, Entity>::Data& _getDataForHandle(Entity, SpriteHandle);
        /* For use by friend classes.
         * It is up to friend class to free the texture */
        SpriteHandle addComponent(Entity, SDL_Texture*, const SpriteOptions&);
        SDL_Texture* setOptions(Entity e, SpriteHandle handle, SDL_Texture* tex, const SpriteOptions& opt);

        friend class TextSystem;

        static Data getDataFromOptions(ID id, SDL_Texture *texture, const SpriteOptions &opt);
    };


    inline ContiguousMultiMap<SpriteSystem::Data, Entity>::Data& SpriteSystem::_getDataForHandle(Entity e, SpriteHandle handle) {
        auto range = _data[e];
        auto it = std::find_if(range.first, range.second, [handle](const ContiguousMultiMap<Data, Entity>::Data& d) {
            return d.data.id == handle;
        });
        if (it == range.second) {
            DEBUGLOG("Range is of size ", range.second - range.first, "\n");
            throw std::invalid_argument("Requested sprite with invalid spritehandle");
        }
        return *it;
    }


}



#endif //FLATLAND_SPRITESYSTEM_H
