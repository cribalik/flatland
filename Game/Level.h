//
// Created by christopher on 2015-06-04.
//

#ifndef FLATLAND_LEVEL_H
#define FLATLAND_LEVEL_H

#include <set>
#include <PhysicsSystem.h>
#include <Matrix.h>
#include "Serialize.h"
#include "GameObject.h"
#include "Actor.h"

class Level : public GameObject {

    enum MapTokens : unsigned char {
        FREE = '-',
        WALL = '#',
    };

    struct MonsterParam {
        double weight = 1;
    };

    std::set<Actor*> _actors;
    fl::Matrix<unsigned char> _map;
    std::map<GameObjectID, MonsterParam> _allowedMonsters;

    Level(Game& g);

public:

    const static std::size_t TILESIZE = 32;

    static Level* Create(Game&, const std::string& path);
    static Level* Load(Game&, std::istream&);

    virtual void activate() override;

    virtual void deactivate() override;

    virtual void logicInit(fl::EntityWrapper wrapper) override;

    virtual void logicDestroy(fl::EntityWrapper wrapper) override;

    /* Read Level from file */
    virtual void serialize(Game& g, std::ostream &os) override;
    virtual void deserialize(Game& g, std::istream& is) override;

    const std::set<Actor*>& actors() const {return _actors;}

private:
    void _processTiles();
    void _parseLevel(const std::string& file);

};


#endif //FLATLAND_LEVEL_H
