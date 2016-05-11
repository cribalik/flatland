//
// Created by cmarte on 5/31/15.
//

#include <SDL_rect.h>
#include "TextSystem.h"
#include "World.h"
#include <SDL2/SDL_ttf.h>

namespace fl {

    void TextSystem::update(Time dt) {

    }

    TextSystem::TextSystem(World &w) : _world(w) {
        // initialize font system
        if (!TTF_WasInit() && TTF_Init()==-1){
            DEBUGLOG("Could not initialize ttf! ", TTF_GetError(), ". Exiting...");
            exit(1);
        }
    }

    TextHandle TextSystem::addComponent(Entity e, const TextOptions & opt) {
        SpriteOptions sopt;
        SDL_Texture* tex = NULL;
        _processTextOptions(opt, sopt, tex);
        DEBUGLOG("Created text: ", opt.text, "\n");
        return _world.getSpriteSystem().addComponent(e, tex, sopt);
    }

    TextHandle TextSystem::addComponent(Entity e, TextOptions && opt) {
        this->addComponent(e, opt);
    }

    void TextSystem::loadFonts(const std::vector<std::string> &paths) {
        std::size_t idx = 0;
        for (const std::string& path : paths) {
            TTF_Font* font = TTF_OpenFont(path.c_str(), FONT_POINTS);
            if (!font) {
                DEBUGLOG("Error opening font from file ", path, " : ", TTF_GetError(), ". Please add files or edit the input vector of fonts in TextSystem::loadFonts call");
                exit(1);
            }
            _fonts.emplace(idx++, font);
        }
    }

    SDL_Texture* TextSystem::_loadTexture(const std::string& str, TTF_Font* font, const SDL_Color& color, unsigned int width)
    {

//		SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
        SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, str.c_str(), color, width);

        if (!surface) return nullptr;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(_world.getWindow().getRenderer(), surface);

        SDL_FreeSurface(surface);

        return texture;
    }

    TextSystem::~TextSystem() {
        for (auto& p : _fonts)
            TTF_CloseFont(p.second);
    }

    void TextSystem::removeEntity(Entity e) {
        /* FIXME: ensure that this is always called at the same time
         * as SpriteSystem::removeEntity */
        /* entity removal is hopefully done in spritesystem.. */
    }

    void TextSystem::removeComponent(Entity e, TextHandle handle) {
        _world.getSpriteSystem().removeComponent(e, handle);
    }

    TextOptions TextSystem::getOptions(Entity e, TextHandle handle) {
        DEBUGLOG("Not yet properly implemented!");
        SpriteOptions s = _world.getSpriteSystem().getOptions(e, handle);
        return TextOptions(s.imagePath, s.box.w, s.offset);
    }

    void TextSystem::setOptions(Entity e, TextHandle handle, const TextOptions &opt) {
        SpriteOptions sopt;
        SDL_Texture* tex = NULL;
        if (opt.text.size() == 0)
            tex = _world.getSpriteSystem()._getDataForHandle(e, handle).data.texture;
        this->_processTextOptions(opt, sopt, tex);
        SDL_Texture* old = _world.getSpriteSystem().setOptions(e, handle, tex, sopt);
        SDL_DestroyTexture(old);
    }

    /* Turns textoption into spriteoption, and if tex is NULL, creates a new texture from the text,
     * otherwise uses the texture already in tex to set spriteoptions */
    void TextSystem::_processTextOptions(const TextOptions& opt, SpriteOptions& sopt, SDL_Texture*& tex) {
        /* Check if font exists */
        auto it_font = _fonts.find(opt.font);
        if (it_font == _fonts.end())
            throw std::invalid_argument("Tried to use a font that is not loaded");
        TTF_Font* font = it_font->second;

        /* Load texture if not already loaded */
        if (!tex) {
            tex = this->_loadTexture(opt.text, font, opt.color, opt.width);
            if (!tex) {
                DEBUGLOG("Coult not load texture for text '", opt.text, "' : TTF: ", TTF_GetError(), " SDL: ",
                         SDL_GetError(), ". Exiting");
                exit(1);
            }
        }

        /* Fix offsets and sizes */
        sopt.autosize = false; /* we fix size ourselves */
        sopt.center = false; /* we fix centering ourselves */
        sopt.offset = opt.offset;
        int w, h;
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        sopt.box.w = w * ((double) opt.textsize / FONT_POINTS);
        sopt.box.h = h * ((double) opt.textsize / FONT_POINTS);
        if (opt.align == TextOptions::CENTER)
            sopt.offset.x -= sopt.box.w / 2.;
        else if (opt.align == TextOptions::RIGHT)
            sopt.offset.x -= sopt.box.w;
        if (opt.vcenter)
            sopt.offset.y -= sopt.box.h / 2.;
    }
}