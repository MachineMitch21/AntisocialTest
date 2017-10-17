CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(antisocial_test)
SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "1")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

file(GLOB SOURCES src/*.cpp src/*.c src/.cc src/*.h src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/external)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/build)

if (UNIX)
target_link_libraries(${PROJECT_NAME} antisocial GL GLEW glfw3)
endif (UNIX)

if (WIN32)
target_link_libraries(${PROJECT_NAME} glew32 opengl32 glfw3 antisocial)
add_definitions(-DGLEW_STATIC -DGLEW_NO_GLU)
endif (WIN32)
