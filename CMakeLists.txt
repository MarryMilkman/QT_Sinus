cmake_minimum_required(VERSION 3.5)

project(CMake_Sinus LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)


set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/coordwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SinusWorker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/statewindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen/QrCode.cpp
)

set(INC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/coordwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/SinusWorker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/statewindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/lib.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen/QrCode.hpp
)

# try link qrcodegen

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen
)

add_custom_target(
    extern_lib
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen
)


##############################################




add_executable(CMake_Sinus
    ${SRC}
    ${INC}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/coordwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/statewindow.ui
)

add_dependencies(CMake_Sinus extern_lib)

target_link_libraries(CMake_Sinus PRIVATE Qt5::Widgets)
target_link_libraries(CMake_Sinus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/qrcodegen/libqrcodegen.a)
