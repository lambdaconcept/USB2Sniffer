cmake_minimum_required (VERSION 3.3)
project(USB2Sniffer)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 COMPONENTS Core Widgets Sql Concurrent Charts REQUIRED)


