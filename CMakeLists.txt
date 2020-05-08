cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(engine/include)

file(GLOB sources
    "src/*.cpp"
)

add_subdirectory(engine)

add_executable(demo ${sources})

link_directories(engine/build)
target_link_libraries(demo engine)
