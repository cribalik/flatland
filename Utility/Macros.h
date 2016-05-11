//
// Created by cmarte on 5/28/15.
//

#ifndef FLATLAND_MACROS_H
#define FLATLAND_MACROS_H

#define STATIC_INITIALIZE(code) \
class _Init {_Init(){ code ; }}; \
static _Init _init;

#endif //FLATLAND_MACROS_H
