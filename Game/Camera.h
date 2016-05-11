//
// Created by cmarte on 6/9/15.
//

#ifndef FLATLAND_CAMERA_H
#define FLATLAND_CAMERA_H


#include <EntityWrapper.h>
#include "GameObject.h"

class Camera : public GameObject, public fl::Updatable {
    fl::World* _targetWorld;
    fl::Entity _targetid;
    int refcount = 0;
    int w,h;
    float xscale,yscale;

    Camera(Game &g, const fl::EntityWrapper &entity, fl::EntityWrapper target) : GameObject(g, entity), _targetid(target), _targetWorld(&target.world()), refcount(0) { }

public:

    void setWidth(int w) {this->w = w;}
    void setHeight(int h) {this->h = h;}
    void setX(int x) {entity().getTransform().x = x;}
    void setY(int y) {entity().getTransform().y = y;}
    void setTarget(fl::EntityWrapper e) {_targetid = e; _targetWorld = &e.world();}

    virtual void activate() override;

    virtual void deactivate() override;

    virtual void update(fl::EntityWrapper, fl::Time);

    virtual void serialize(Game &game, std::ostream &os) override;

    virtual void deserialize(Game &game1, std::istream &is) override;

    virtual void logicInit(fl::EntityWrapper) override {++refcount;};

    virtual void logicDestroy(fl::EntityWrapper) override {--refcount; if (!refcount) delete this;}

    virtual void updateInit(fl::EntityWrapper w) override {++refcount;}

    virtual void updateDestroy(fl::EntityWrapper w) override {--refcount; if (!refcount) delete this;}

    static Camera* Create(Game&, fl::EntityWrapper target, int w = 1920, int h = 1080);

public:


};


#endif //FLATLAND_CAMERA_H
