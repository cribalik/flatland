//
// Created by cmarte on 6/9/15.
//

#include "Camera.h"
#include "Game.h"

void Camera::activate() {
    entity().addUpdateListener(this);
}

void Camera::deactivate() {
    entity().removeUpdateListener(this);
}

void Camera::serialize(Game &game, std::ostream &os) {
    GameObject::serialize(game, os);
}

void Camera::deserialize(Game &game, std::istream &is) {
    DEBUGLOG_AND_DIE("Not inplemented");
}

Camera *Camera::Create(Game &game, fl::EntityWrapper target, int w, int h) {
    fl::EntityWrapper e = game.getWorld().createEntity(static_cast<fl::Tag>(GameObjectID::Camera));
    Camera* cam = new Camera(game, e, target);
    cam->h = h; cam->w = w;
    cam->xscale = 1920/w; cam->yscale = 1080/h;
    DEBUGLOG(cam->xscale, ' ', cam->yscale, '\n');
    SDL_RenderSetLogicalSize(game.getWorld().getRenderer(), w,h);
    e.addLogicComponent(cam);
    return cam;
}

void Camera::update(fl::EntityWrapper e, fl::Time) {
    const auto& tr = _targetWorld->getTransform(_targetid);
    SDL_Rect r { (-tr.x + w/2), -tr.y + h/2 , 1920, 1080};
    DEBUGLOG(_targetid, '\n', r.x, ' ' ,r.y , '\n');
    SDL_RenderSetViewport(game().getWorld().getRenderer(), &r);
}

