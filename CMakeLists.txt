CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(antisocial_test)
SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "1")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

file(GLOB SOURCES src/*.cpp src/*.c src/.cc src/*.h src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_definitions()
include_directories(${PROJECT_SOURCE_DIR}/external)
link_directories(${PROJECT_SOURCE_DIR}/lib)

if (UNIX)
target_link_libraries(${PROJECT_NAME} antisocial)
endif (UNIX)

if (WIN32)
target_link_libraries(${PROJECT_NAME} antisocial)
endif (WIN32)
