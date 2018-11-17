cmake_minimum_required (VERSION 3.3)
project(USB2Sniffer)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory("3rdpartylibs/videotimeline")
include_directories("3rdpartylibs/videotimeline/")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(SRC_DIR "src/")
set(INC_DIR "include/")



set(USB2SNIFFER_SRC_FILES
    ${SRC_DIR}/MainWindow.cpp
    ${SRC_DIR}/USBDataItem.cpp
	${SRC_DIR}/USBDataModel.cpp
 )


set(USB2SNIFFER_INCLUDE_FILES
	${INC_DIR}/MainWindow.hpp
	${INC_DIR}/USBDataItem.hpp
	${INC_DIR}/USBDataModel.hpp

 )

include_directories(${INC_DIR})

add_executable(usb2sniffer ${USB2SNIFFER_INCLUDE_FILES} ${SRC_DIR}/main.cpp ${USB2SNIFFER_SRC_FILES})
target_link_libraries(usb2sniffer  WidgetsBased)
qt5_use_modules(usb2sniffer Core Widgets)




