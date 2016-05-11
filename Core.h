//
// Created by cmarte on 5/26/15.
//

#ifndef FLATLAND_CORE_H
#define FLATLAND_CORE_H

#define DEBUG

#ifdef DEBUG
#include <iostream>
template<typename T>
void printvar(const T& t) {
    std::cerr << t;
}
template<typename T, typename... Args>
void printvar(const T& t, Args... args) {
    std::cerr << t;
    printvar(args...);
}
#define DEBUGLOG(...) printvar("In file ", __FILE__, " line ", __LINE__, ":\n", __VA_ARGS__, "\n");
#define DEBUGLOG_AND_DIE(...) {DEBUGLOG(__VA_ARGS__); exit(1);}
#define FL_STUB std::cerr << "Unimplemented method in " << __FILE__ << " line " << __LINE__ << std::endl;
#else
#define DEBUGLOG(...)
#define DEBUGLOG_AND_DIE(...)
#define FL_STUB
#endif

#include <cstdint>

namespace fl {
    typedef int Entity;
    typedef double Time;
    typedef std::size_t ID;
    typedef std::size_t Tag;
    class Void {};
    struct Transform {
        double x,y;
    };
    class World;
}

#endif //FLATLAND_CORE_H
