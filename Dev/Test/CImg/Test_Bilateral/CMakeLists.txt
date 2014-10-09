cmake_minimum_required(VERSION 2.6)
project(start_cimg)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Start_CImg_SRCS src/Start_CImg.cpp main.cpp)

qt4_automoc(${Start_CImg_SRCS})
add_executable(start_cimg ${Start_CImg_SRCS})
target_link_libraries(start_cimg ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS start_cimg RUNTIME DESTINATION bin)
