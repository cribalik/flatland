cmake_minimum_required(VERSION 3.2)
project(flatland)

include(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(flatland ${SOURCE_FILES} World.cpp World.h EntityWrapper.h Systems.h PhysicsSystem.cpp PhysicsSystem.h SpriteSystem.cpp SpriteSystem.h Core.h fl_SDLInit.h Window.cpp Window.h Renderer.cpp Renderer.h Utility/Table.h Game/Tag.h Game/Tags.h Game/Tag.cpp Utility/IndexFactory.h Utility/Heap.h Utility/IDFactory.cpp Utility/IDFactory.h InputSystem.cpp InputSystem.h System.h Geometry.h Utility/ContiguousMap.h Utility/ContiguousMultiMap.h Utility/Macros.h DefaultTags.h EntityWrapper.cpp SpriteComponent.h PhysicsComponent.h InputComponent.h LogicSystem.cpp LogicSystem.h LogicComponent.h Game/Game.cpp Game/Game.h Game/Menu.cpp Game/Menu.h TextSystem.cpp TextSystem.h TextComponent.h Fonts.h Game/Level.cpp Game/Level.h Game/Serialize.h Game/Actor.h Game/Actor.cpp Game/GameObject.cpp Game/GameObject.h Game/Ball.cpp Game/Ball.h Action.h Matrix.h Game/Stairs.cpp Game/Stairs.h Game/Gold.cpp Game/Gold.h Game/Camera.cpp Game/Camera.h Game/Player.cpp Game/Player.h Game/TopDownMovement.cpp Game/TopDownMovement.h Game/Weapon.cpp Game/Weapon.h Game/Sword.cpp Game/Sword.h CollisionSystem.cpp CollisionSystem.h CollisionComponent.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
