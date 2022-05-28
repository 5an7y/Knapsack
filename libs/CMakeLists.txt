set (CMAKE_CXX_STANDARD 11)

add_library(
    Instancia
    Instancia/Instancia.hpp
    Instancia/Instancia.cpp
)

add_library(
    SolucionDP
    SolucionDP/SolucionDP.hpp
    SolucionDP/SolucionDP.cpp
)

add_library(
    Iterativa
    Iterativa/Iterativa.hpp
    Iterativa/Iterativa.cpp
)

add_library(
    Genetico
    Genetico/Genetico.hpp
    Genetico/Genetico.cpp
)

target_include_directories(Instancia PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Instancia")
target_include_directories(SolucionDP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/SolucionDP")
target_include_directories(Iterativa PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Iterativa")
target_include_directories(Genetico PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Genetico")

target_link_libraries(SolucionDP PRIVATE Instancia)
target_link_libraries(Iterativa PRIVATE Instancia)
target_link_libraries(Genetico PRIVATE Instancia)