cmake_minimum_required(VERSION 2.6)
project(filtre_bilateral_naif)

add_executable(filtre_bilateral_detail src/filtrebilateral.cpp main.cpp)

install(TARGETS filtre_bilateral_naif RUNTIME DESTINATION bin)
