cmake_minimum_required(VERSION 3.5)

project(Special_shapedFactory VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)




set(PROJECT_SOURCES
        main.cpp
        factory.cpp
        factory.h
        factory.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Special_shapedFactory
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        startscreen.h
        startscreen.cpp


        endscreen.h
        endscreen.cpp
        ore.h
        ore.cpp
        res.qrc
        deliverycentre.h
        deliverycentre.cpp
        Miner.h
        Miner.cpp
        MapWidget.h
        MapWidget.cpp
        Belt.h
        Belt.cpp
        Cutter.h
        Cutter.cpp
        Trash.h
        Trash.cpp
        Spade.h
        Spade.cpp
        OverlayWindow.h
        OverlayWindow.cpp
        Shop.h
        Shop.cpp
        Help.h
        Help.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Special_shapedFactory APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Special_shapedFactory SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Special_shapedFactory
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Special_shapedFactory PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Special_shapedFactory PRIVATE Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Special_shapedFactory)
endif()
set_target_properties(Special_shapedFactory PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Special_shapedFactory
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Special_shapedFactory)
endif()
