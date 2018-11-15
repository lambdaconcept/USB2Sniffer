cmake_minimum_required (VERSION 3.3)
project(USB2Sniffer)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(SRC_DIR "src/")
set(INC_DIR "include/")



set(USB2SNIFFER_SRC_FILES
    ${SRC_DIR}/MainWindow.cpp
 )


set(USB2SNIFFER_INCLUDE_FILES
	${INC_DIR}/MainWindow.hpp
 )

include_directories(${INC_DIR})

add_executable(usb2sniffer ${USB2SNIFFER_INCLUDE_FILES} ${SRC_DIR}/main.cpp ${USB2SNIFFER_SRC_FILES})

qt5_use_modules(usb2sniffer Core Widgets)




