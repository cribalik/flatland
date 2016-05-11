/*
 * File:   Renderer.h
 * Author: cmarte
 *
 * Created on December 23, 2014, 5:28 PM
 */

#ifndef FLATLAND_RENDERER_H
#define FLATLAND_RENDERER_H

#include <stack>
#include <SDL2/SDL_render.h>

namespace fl {

    class Renderer {
    public:
        Renderer(SDL_Renderer* renderer) : r(renderer) {offset.push( {0,0} );};
        Renderer(Renderer&&) = default;
        Renderer(const Renderer&) = delete;
        int renderCopyEx(
                SDL_Texture * texture,
                const SDL_Rect * srcrect,
                const SDL_Rect * dstrect,
                const double angle,
                const SDL_Point *center,
                const SDL_RendererFlip flip);
        void pushOffset(int x, int y);
        void popOffset();
        SDL_Renderer* getSDLRenderer() {return r;};
        operator SDL_Renderer*() {return r;}
        virtual ~Renderer() {}
    private:
        Renderer() : r(nullptr) {offset.push( {0,0} );}
        SDL_Renderer* r;
        std::stack<SDL_Point> offset;
        friend class Window;
    };

    inline void Renderer::pushOffset(int dx, int dy) {
        offset.push( {offset.top().x + dx, offset.top().y + dy} );
    }

    inline void Renderer::popOffset() {
        offset.pop();
    }

    inline int Renderer::renderCopyEx(
            SDL_Texture * texture,
            const SDL_Rect * srcrect,
            const SDL_Rect * dstrect,
            const double angle,
            const SDL_Point *center,
            const SDL_RendererFlip flip) {

        SDL_Rect dest (*dstrect);
        dest.x += offset.top().x;
        dest.y += offset.top().y;

        return SDL_RenderCopyEx(r, texture, srcrect, &dest, angle, center, flip);
    }

}

#endif //FLATLAND_RENDERER_H
