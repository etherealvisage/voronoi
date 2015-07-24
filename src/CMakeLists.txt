add_definitions(-Wextra -Wall -std=c++11 -O3)

add_executable(voronoi main.cpp voronoi.cpp)

target_link_libraries(voronoi m)
