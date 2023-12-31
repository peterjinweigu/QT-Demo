cmake_minimum_required(VERSION 3.5)

project(Qt-Demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Core Gui QuickWidgets)
message("Building for QT${QT_VERSION_MAJOR}")
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui QuickWidgets)

# todo use file glob to autodetect new files
set(PROJECT_SOURCES
        src/ui/main.cpp
        src/ui/mainwindow/mainwindow.cpp
        src/ui/mainwindow/mainwindow.h
        src/ui/mainwindow/mainwindow.ui
        src/shared/types.cpp src/shared/types.h
)

set(IO_Headers src/io/can.h)
set(IO_Sources src/io/can.cpp)
set(MockIO_Sources src/mock_io/can.cpp)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt-Demo
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${IO_Headers}
            ${IO_Sources}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET Qt-Demo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(Qt-Demo SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(Qt-Demo
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()

target_link_libraries(Qt-Demo
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::QuickWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Qt-Demo)
endif ()
set_target_properties(Qt-Demo PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Qt-Demo
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qt-Demo)
endif ()
