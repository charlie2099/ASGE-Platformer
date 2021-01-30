## local variable for managing the game target
set(GAME ${PROJECT_NAME})

## glob is useful but not reliant in compilation so just use it for headers ##
file(GLOB_RECURSE HEADER_LIST
        LIST_DIRECTORIES FALSE
        CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/game/*.hpp
        ${CMAKE_SOURCE_DIR}/src/game/*.h)

## the ASGE Game, which spawns the Game window ##
add_executable(
        ${GAME} ${HEADER_LIST}
        ## source code files for app here ##
        game/main.cpp
        game/game.cpp game/GameObject.cpp game/GameObject.hpp game/Vector2.cpp game/Vector2.hpp game/SpriteComponent.cpp game/SpriteComponent.hpp game/Player.cpp game/Player.hpp)

## configure the target ##
list(APPEND LIBS ${CMAKE_DL_LIBS})
configure_target(${GAME} ${CMAKE_CURRENT_SOURCE_DIR} "${HEADER_LIST}" "${LIBS}")
add_asge_dependency(${GAME})

## game data ##
include(tools/gamedata)
add_gamedata(${GAME} ${CMAKE_SOURCE_DIR}/data)
