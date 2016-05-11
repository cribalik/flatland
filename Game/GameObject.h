//
// Created by christopher on 2015-06-04.
//

#ifndef FLATLAND_GAMEOBJECT_H
#define FLATLAND_GAMEOBJECT_H

#include <World.h>
#include "Serialize.h"

class Game;

enum class GameObjectID : fl::Tag {
    #define GAMEOBJECT(g) g ,
    #include "GameObjects.h"
    #undef GAMEOBJECT
};

extern const char* game_object_names[];

class GameObject : public fl::Logic, public Serializable {
    fl::EntityWrapper _entity;
    Game& _game;
public:
    fl::EntityWrapper getEntity() {return _entity;}
    GameObject(Game& g, fl::EntityWrapper entity) : _entity(entity), _game(g) {entity.addLogicComponent(this);}
    void destroy() {_entity.destroy();}
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void serialize(Game &game, std::ostream &os) override {os << _entity.getTag() << ' ';}
    virtual void deserialize(Game&, std::istream& is) override {}
    static GameObject* Load(Game &, std::istream &);
    fl::EntityWrapper& entity() {return _entity;}
    Game& game() {return _game;}
    GameObjectID type() {return static_cast<GameObjectID>(_entity.getTag());}

    operator const char*() const {return game_object_names[_entity.getTag()];}

    std::string toString() {return game_object_names[_entity.getTag()];}
};

#endif //FLATLAND_GAMEOBJECT_H
