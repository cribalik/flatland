//
// Created by cmarte on 5/27/15.
//

#ifndef FLATLAND_SYSTEM_H
#define FLATLAND_SYSTEM_H

#include "Core.h"

#define DEFINE_COMPONENT_OPTIONS(sysname) using sysname##Options =
#define DEFINE_COMPONENT_HANDLE(sysname) using sysname##Handle =
#define DEFAULT_COMPONENT_HANDLE(sysname) typedef Void sysname##Handle;
#define DECLARE_SYSTEM_METHODS(sysname) \
private: \
World& _world; \
public: \
explicit sysname##System(World& w); \
sysname##System(const sysname##System&) = delete; \
sysname##Handle addComponent(Entity e, const sysname##Options&); \
sysname##Handle addComponent(Entity e, sysname##Options&&); \
void removeComponent(Entity e, sysname##Handle handle); \
sysname##Options getOptions(Entity e, sysname##Handle handle); \
void setOptions(Entity e, sysname##Handle handle, const sysname##Options& opt); \
void removeEntity(Entity e); \
void update(Time dt);
#define DECLARE_SYSTEM_METHODS_DEFAULT_HANDLE(sysname) \
private: \
World& _world; \
public: \
explicit sysname##System(World& w); \
sysname##System(const sysname##System&) = delete; \
sysname##Handle addComponent(Entity e, const sysname##Options&); \
sysname##Handle addComponent(Entity e, sysname##Options&&); \
void removeComponent(Entity e, sysname##Handle handle) {}; \
sysname##Options getOptions(Entity e, sysname##Handle handle) {}; \
void setOptions(Entity e, sysname##Handle handle, const sysname##Options& opt) {}; \
void removeEntity(Entity e); \
void update(Time dt);

#endif //FLATLAND_SYSTEM_H
