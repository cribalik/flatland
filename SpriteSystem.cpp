//
// Created by cmarte on 5/26/15.
//

#include "SpriteSystem.h"
#include <map>
#include "World.h"
#include "Utility/IDFactory.h"

namespace fl {

    SpriteSystem::SpriteSystem(World &w) : _world(w)
    {}

    void SpriteSystem::update(Time) {
        /* Copy sprite vector and sort it by z, FIXME: very slow, use openGL instead */
        typedef ContiguousMultiMap<Data, Entity>::Data Sprite;
        std::vector<Sprite> sprites(_data.begin(), _data.end());
        std::sort(sprites.begin(), sprites.end(), [](const Sprite& a, const Sprite& b) {
            return a.data.z < b.data.z;
        });
        for (auto& p : sprites) {
            auto& tr = _world.getTransform(p.index);
            auto& d = p.data;
            SDL_Rect dst {
                    static_cast<int>(tr.x + d.xoffset + d.xalign),
                    static_cast<int>(tr.y + d.yoffset + d.yalign),
                    static_cast<int>(d.w),
                    static_cast<int>(d.h)
            };
            SDL_RenderCopyEx(_world.getRenderer(), p.data.texture, NULL, &dst, d.rot, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
        }
    }

    SpriteHandle SpriteSystem::addComponent(Entity e, const SpriteOptions & opt) {
        return this->addComponent(e, _loadCachedTexture(opt.imagePath), opt);
    }

    SpriteHandle SpriteSystem::addComponent(Entity e, SpriteOptions && opt) {
        return this->addComponent(e, opt);
    }

    void SpriteSystem::removeComponent(Entity e, SpriteHandle handle) {
        auto range = _data[e];
        auto it = std::find_if(range.first, range.second, [handle](const ContiguousMultiMap<Data, Entity>::Data& d) {
            return d.data.id == handle;
        });
        if (it == range.second)
            return;
        DEBUGLOG("Removing Sprite ", handle, " from entity ", e, "\n");
        _data.erase(it);
    }

    void SpriteSystem::removeEntity(Entity e) {
        IDFactory::returnID(_data[e].first->data.id);
        DEBUGLOG("Removing all sprites for entity ", e, "\n");
        _data.erase(e);
    }

    SDL_Texture* SpriteSystem::_loadCachedTexture(const std::string& path)
    {
        /* TODO: actually release textures */
        static std::map<std::string, SDL_Texture*> items;

        auto item = items.find(path);
        // if not in cache, load texture from file
        if (item == items.end()) {
            DEBUGLOG("Loading texture '", path, "'\n");
            SDL_Texture* tex = _loadTexture(path.c_str(), _world.getRenderer());
            if (!tex) {
                DEBUGLOG("Could not load texture from file '", path, " : ", SDL_GetError(), '\n');
                exit(EXIT_FAILURE);
            }
            items.emplace(path, tex);
            DEBUGLOG("Texture loaded!\n");
            return tex;
        }
        // otherwise return cached value
        else
            return item->second;
    }

    SDL_Texture *SpriteSystem::_loadTexture(const char* path, SDL_Renderer *renderer, int* h, int* w) {

        SDL_Texture* r = nullptr;

        SDL_Surface* s = IMG_Load(path);
        if (!s)
            return nullptr;

        if (w) *w = s->w;
        if (h) *h = s->h;

        r = SDL_CreateTextureFromSurface(renderer, s);

        SDL_FreeSurface(s);

        return r;
    }

    SpriteHandle SpriteSystem::addComponent(Entity e, SDL_Texture *texture, const SpriteOptions &opt) {
        ID id = IDFactory::getID();
        DEBUGLOG("Created Sprite for entity ", e, " with ID ", id, '\n');
        Data d = getDataFromOptions(id, texture, opt);

       DEBUGLOG("Number of sprites before add: ", _data.size());
        _data.insert(e, d);
        DEBUGLOG("Number of sprites after add: ", _data.size());
        return d.id;
    }

    SpriteSystem::Data SpriteSystem::getDataFromOptions(ID id, SDL_Texture *texture, const SpriteOptions &opt) {
        Data d= {
                id,
                texture,
                opt.z,
                opt.rot,
                opt.box.w,
                opt.box.h,
                opt.offset.x,
                opt.offset.y,
                0,0,
        };
        if (opt.autosize) {
            int iw, ih;
            SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
            d.w = static_cast<double>(iw);
            d.h = static_cast<double>(ih);
        }
        if (opt.center) {
            d.xalign = -d.w/2.;
            d.yalign = -d.h/2.;
        }
        return d;
    }

    SpriteOptions SpriteSystem::getOptions(Entity e, SpriteHandle handle) {
        const Data& d = _getDataForHandle(e, handle).data;
        return SpriteOptions("", Box{d.w, d.h}, Point{d.xoffset, d.yoffset});
    }

    void SpriteSystem::setOptions(Entity e, SpriteHandle handle, const SpriteOptions& opt) {
        Data& d = _getDataForHandle(e, handle).data;
        /* TODO: release texture or tell cache we dont need it anymore */

        if (opt.imagePath.size() > 0)
            d = getDataFromOptions(d.id, _loadCachedTexture(opt.imagePath), opt);
        else
            d = getDataFromOptions(d.id, d.texture, opt);
    }

    /* For use by friend systems.
     * Updates a sprite with new options.
     * If tex is not NULL, the texture will be changed, but the old texture will NOT be destroyed!
     * The texture that was being used at the time of calling is returned,
     * so that the caller may choose to destroy it */
    SDL_Texture* SpriteSystem::setOptions(Entity e, SpriteHandle handle, SDL_Texture *tex, const SpriteOptions &opt) {
        Data& d = _getDataForHandle(e, handle).data;
        /* FIXME: destroy texture or inform cache that it's gone */
        SDL_Texture* prevtex = d.texture;
        if (tex)
            d = getDataFromOptions(d.id, tex, opt);
        else
            d = getDataFromOptions(d.id, d.texture, opt);
        return prevtex;
    }
}
