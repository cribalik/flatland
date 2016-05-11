//
// Created by christopher on 2015-06-04.
//

#ifndef FLATLAND_SERIALIZE_H
#define FLATLAND_SERIALIZE_H

#include <iostream>
#include <exception>

class Game;

class SerializeException : public std::exception {
    const char* msg;
public:
    SerializeException(const char* msg) : msg(msg) {}
    virtual const char* what() const noexcept override {return msg;}
};

class Serializable {
    virtual void serialize(Game &game, std::ostream &os) = 0;
    virtual void deserialize(Game &game, std::istream &is) = 0;
};

#endif //FLATLAND_SERIALIZE_H
