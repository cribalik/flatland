//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_GEOMETRY_H
#define FLATLAND_GEOMETRY_H

#include <cmath>

namespace fl {

    struct Box {
        double w,h;
    };
    struct Point {
        double x,y;
        double norm() const {return std::sqrt(x*x + y*y);}
    };
    struct Vel {
        double vx,vy;
    };
    struct Rect {
        double x,y,w,h;
    };
}

#endif //FLATLAND_GEOMETRY_H
