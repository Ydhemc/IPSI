cmake_minimum_required(VERSION 3.0)

project(joueurs)

find_package(Threads)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
add_compile_options(-Wall -Wpedantic)


set(SRCS
    joueur.cc
    joueur_random.cc
    joueur_manuel.cc
    joueur_montecarlo_.cc
    joueur_alphabeta.cc
    ProjetMehdy-Oumar-Lyna/node.cc
    ProjetMehdy-Oumar-Lyna/save.cc
    ProjetMehdy-Oumar-Lyna/apprentissage.cc
    )
    
set(HEADERS
    joueur.hh
    joueur_random.hh
    joueur_manuel.hh
    joueur_montecarlo_.hh
    joueur_alphabeta.hh
    ProjetMehdy-Oumar-Lyna/node.hh
    ProjetMehdy-Oumar-Lyna/save.hh
    ProjetMehdy-Oumar-Lyna/apprentissage.hh
    )

add_library(joueurs ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
