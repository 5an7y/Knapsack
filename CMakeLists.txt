cmake_minimum_required(VERSION 3.2)
project(Knapsack)
set (CMAKE_CXX_STANDARD 14)

add_subdirectory(libs)

add_executable(Knapsack Main.cpp)

target_link_libraries(Knapsack PRIVATE Instancia)
target_link_libraries(Knapsack PRIVATE SolucionDP)
target_link_libraries(Knapsack PRIVATE Iterativa)
target_link_libraries(Knapsack PRIVATE Genetico)