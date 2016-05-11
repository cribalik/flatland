//
// Created by christopher on 2015-06-04.
//

#include "Level.h"
#include "Game.h"
#include "Stairs.h"
#include "Gold.h"
#include "Player.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, fl::Wall w) {
    os << w.x << ' ' << w.y << ' ' << w.w << ' ' << w.h << '\n';
}

std::istream& operator>>(std::istream& is, fl::Wall w) {
    is >> w.x >> w.y >> w.w >> w.h;
}

void Level::serialize(Game& g, std::ostream &os) {
    /* Serialize parent */
    GameObject::serialize(g, os);

    /* walls */
    os << _map.rows() << ' ' << _map.cols() << '\n';
    os << _map;

    /* Actors */
    os << _actors.size() << '\n';
    for (Actor* e : _actors)
        e->serialize(g, os);
}

void Level::deserialize(Game& g, std::istream &is) {
    /* Deserialize parent */
    GameObject::deserialize(g, is);

    std::string levelfile;
    is >> levelfile;
    /* Tiles */
    this->_parseLevel(levelfile);

    /* Actors */
    std::size_t num;
    is >> num;
    _actors.clear();
    for (std::size_t i = 0; i < num; ++i) {
        GameObject* go = GameObject::Load(g, is);
        Actor* actor = dynamic_cast<Actor*>(go);
        if (!actor)
            DEBUGLOG_AND_DIE("Error when reading actors for Levels")
        _actors.insert(actor);
    }
};

void Level::activate() {
    /* Insert walls into physics system */
    for (std::size_t i = 0; i < _map.cols(); ++i) {
        for (std::size_t j = 0; j < _map.rows(); ++j) {
            if (_map(i,j) != WALL) continue;
            this->getEntity().world().getPhysicsSystem().addWall({
                 (double) j * TILESIZE,
                 (double) i * TILESIZE,
                 (double) TILESIZE,
                 (double) TILESIZE
            });
        }
    }
    /* Activate actors */
    for (auto actor : actors())
        actor->activate();
    /* Find player and set camera on player */
//    for (auto actor : actors())
//        if (actor->type() == GameObjectID::Player) {
//            game().setCameraOn(actor->entity());
//            break;
//        }

    /* draw the floor and walls */
    for (std::size_t i = 0; i < _map.cols(); ++i)
    for (std::size_t j = 0; j < _map.rows(); ++j) {
        switch (_map(i,j)) {
            case FREE: {
                fl::SpriteOptions sopt (
                "/home/cmarte/ClionProjects/flatland/Game/res/Sprites/floor.jpg",
                        fl::Box{TILESIZE, TILESIZE},
                        fl::Point{(double) j*TILESIZE, (double) i*TILESIZE},
                        0
                ); sopt.center = false;
                entity().addSpriteComponent(sopt);
                break;
            };

                break;
            case WALL: {
                fl::SpriteOptions sopt(
                        "/home/cmarte/ClionProjects/flatland/Game/res/Sprites/wall.jpg",
                        fl::Box{TILESIZE, TILESIZE},
                        fl::Point{(double) j * TILESIZE, (double) i * TILESIZE},
                        0
                );
                sopt.center = false;
                entity().addSpriteComponent(sopt);
                break;
            }
            default:
                DEBUGLOG_AND_DIE("Error while parsing map : unrecognized symbol ", _map(i,j), '\n');
        }
    }
}

void Level::deactivate() {
    FL_STUB;
    DEBUGLOG_AND_DIE("Deactivate in Level not implemented!");
}

void Level::logicInit(fl::EntityWrapper) {

}

void Level::logicDestroy(fl::EntityWrapper) {
    delete this;
}

Level::Level(Game& g)
        : GameObject(g, g.getWorld().createEntity(static_cast<fl::Tag>(GameObjectID::Level), fl::Transform{}, this)) {}

void Level::_processTiles() {
    /* check if a tile blocks en entrance to a tunnel */
    auto isBlocking = [this](std::size_t i, std::size_t j) {
        return ((_map(i+1,j+1) == WALL && _map(i+1,j) != WALL && _map(i+1, j-1) == WALL)
            || (_map(i-1,j+1) == WALL && _map(i-1,j) != WALL && _map(i-1, j-1) == WALL)
            || (_map(i-1,j+1) == WALL && _map(i,j+1) != WALL && _map(i+1, j+1) == WALL)
            || (_map(i-1,j-1) == WALL && _map(i,j-1) != WALL && _map(i+1, j-1) == WALL));
    };

    std::vector<std::pair<std::size_t,std::size_t>> free;
    for (std::size_t i = 0; i < _map.cols(); ++i)
    for (std::size_t j = 0; j < _map.rows(); ++j)
        if (_map(i,j) == FREE && !isBlocking(j,i)) free.push_back({j,i});
    std::random_shuffle(free.begin(), free.end());

    /* Place stairs first. */
    auto pos = free.back(); free.pop_back();
    _actors.insert( Stairs::Create(game(), fl::Point{(double) pos.first*TILESIZE + TILESIZE/2, (double) pos.second*TILESIZE + TILESIZE/2}) );

    /* Then place player */
    pos = free.back(); free.pop_back();
    _actors.insert( Player::Create(game(), fl::Point{(double) pos.first*TILESIZE + TILESIZE/2, (double) pos.second*TILESIZE + TILESIZE/2}) );

    /* Fill a percent of tiles with something, but at least 3 tiles */
    std::size_t x = std::max(free.size()/30, (std::size_t) 3);
    if (free.size() < 3) DEBUGLOG_AND_DIE("Level too small, no nonblocking tiles!!\n");
    for (std::size_t i = 0; i < x; ++i) {
        /* TODO: implement */
        pos = free.back(); free.pop_back();
        /* add piles of 20 - 40 gold */
        _actors.insert( Gold::Create(
                game(),
                (rand()%30) + 10,
                fl::Point{
                        (double) pos.first*TILESIZE + TILESIZE/2,
                        (double) pos.second*TILESIZE + TILESIZE/2
                }
        ) );
    }

}

void Level::_parseLevel(const std::string &file) {
    std::ifstream is(file);
    DEBUGLOG("Parsing Level file ", file, "\n");
    if (!is) DEBUGLOG_AND_DIE("Opening Level file '", file, "' failed!\n");
    std::size_t N,M;
    is >> N >> M;
    DEBUGLOG(N,' ',M,'\n');
    _map = {N,M};
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < M; ++j)
            is >> _map(i, j);
        is.get();
    }
    DEBUGLOG(_map, '\n');

    for (auto& v : _map) is >> v;

    /* Parse configurations */
    std::string c;
    while (is >> c) {
        if (c[0] == '#') continue;
        if (c == "addMonster") {
            std::size_t id; is >> id;
            _allowedMonsters.emplace(static_cast<GameObjectID>(id), MonsterParam{});
        }
        else if (c == "setMonsterAppearanceWeight") {
            std::size_t id; is >> id;
            double weight; is >> weight;
            is >> _allowedMonsters[static_cast<GameObjectID>(id)].weight;
        }
        else {
            DEBUGLOG_AND_DIE("Unrecognized command ", c, " when reading level file\n");
        }

    }
    this->_processTiles(); /* place chests, enemy spawn locations, stairs etc. */
}

Level* Level::Load(Game& game, std::istream& is) {
    Level* level = new Level(game);
    level->deserialize(game, is);
    return level;
}

Level* Level::Create(Game& game, const std::string &path) {
    Level* level = new Level(game);
    level->_parseLevel(path);
    return level;
}
