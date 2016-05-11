//
// Created by christopher on 2015-06-04.
//

#include "GameObject.h"
#include "Ball.h"
#include "Level.h"
#include "Menu.h"
#include "Stairs.h"
#include "Gold.h"
#include "Camera.h"
#include "Player.h"

const char* game_object_names[] = {
    #define GAMEOBJECT(g) #g ,
    #include "GameObjects.h"
    #undef GAMEOBJECT
};

GameObject *GameObject::Load(Game &game, std::istream &is) {
    fl::Tag id;
    is >> id;
    switch (static_cast<GameObjectID>(id)) {
#define GAMEOBJECT(a) \
    case GameObjectID::a: { \
        GameObject* go = a::Load(game,is); \
        if (!go) DEBUGLOG_AND_DIE("Creating object #a from stream failed\n"); \
        return go; \
    }
#include "GameObjects.h"
#undef GAMEOBJECT
    default:
        throw SerializeException("Not a valid gameobject id in beginning of file");
    }
}

//GameObject *GameObject::Create(Game &game, GameObjectID id) {
//    switch (id) {
//        #define GAMEOBJECT(a) \
//        case GameObjectID::a: { \
//            return a::Create(game); \
//        }
//        #include "GameObjects.h"
//        #undef GAMEOBJECT
//        default:
//            throw SerializeException("Not a valid gameobject id in beginning of file");
//    }
//}
