cmake_minimum_required(VERSION 3.10)
project(FantasyAdvanture)

# Add your source files
file(GLOB_RECURSE SOURCE_FILES "utils/*.cpp")

# Add your header files
file(GLOB_RECURSE HEADER_FILES "utils/*.h")

add_executable(fantasy_adventure fantasy_adventure.cpp ${SOURCE_FILES} ${HEADER_FILES})

find_package(SFML COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(fantasy_adventure PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
