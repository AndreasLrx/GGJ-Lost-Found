cmake_minimum_required (VERSION 3.8)

project(GJGameJam CXX)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)

set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window audio system REQUIRED)

# Root Directory
set(SRCROOT ${PROJECT_SOURCE_DIR}/srcs)
set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRC
	${SRCROOT}/main.cpp
)

# GameEngine Directory
set(SRCROOT ${PROJECT_SOURCE_DIR}/srcs/GameEngine)
set(INCROOT ${PROJECT_SOURCE_DIR}/include/GameEngine)
set(SRC
    ${SRC}
	${SRCROOT}/AssetManager.cpp
	${INCROOT}/AssetManager.hpp
	${SRCROOT}/Core.cpp
	${INCROOT}/Core.hpp
	${SRCROOT}/InputManager.cpp
	${INCROOT}/InputManager.hpp
	${SRCROOT}/StateMachine.cpp
	${INCROOT}/StateMachine.hpp
)

# GUI Directory
set(SRCROOT ${PROJECT_SOURCE_DIR}/srcs/GUI)
set(INCROOT ${PROJECT_SOURCE_DIR}/include/GUI)
set(SRC
    ${SRC}
	${SRCROOT}/Button.cpp
	${INCROOT}/Button.hpp
	${SRCROOT}/CheckBox.cpp
	${INCROOT}/CheckBox.hpp
	${SRCROOT}/ClickableText.cpp
	${INCROOT}/ClickableText.hpp
	${SRCROOT}/GUIItem.cpp
	${INCROOT}/GUIItem.hpp
	${SRCROOT}/GUIManager.cpp
	${INCROOT}/GUIManager.hpp
	${SRCROOT}/RadioButtons.cpp
	${INCROOT}/RadioButtons.hpp
	${SRCROOT}/ScrollBar.cpp
	${INCROOT}/ScrollBar.hpp
	${SRCROOT}/TextButton.cpp
	${INCROOT}/TextButton.hpp
	${SRCROOT}/TextField.cpp
	${INCROOT}/TextField.hpp
	${SRCROOT}/TextItem.cpp
	${INCROOT}/TextItem.hpp
	${SRCROOT}/TextShape.cpp
	${INCROOT}/TextShape.hpp
)

# States Directory
set(SRCROOT ${PROJECT_SOURCE_DIR}/srcs/States)
set(INCROOT ${PROJECT_SOURCE_DIR}/include/States)
set(SRC
    ${SRC}
	${SRCROOT}/GameState.cpp
	${INCROOT}/GameState.hpp
	${SRCROOT}/MenuState.cpp
	${INCROOT}/MenuState.hpp
)

add_executable (alien ${SRC})
target_link_libraries(alien sfml-graphics sfml-window sfml-audio sfml-system)
