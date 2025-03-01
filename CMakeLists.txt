cmake_minimum_required(VERSION 3.5)

project(ga VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h

    src/mainwindow.ui

    include/core/Board.h
    src/core/Board.cpp

    include/core/Player.h
    src/core/Player.cpp

    include/core/ScoreTracker.h

    include/strategy/PlayerStrategy.h

    include/strategy/HumanInputStrategy.h

    include/engine/GameEngine.h
    src/engine/GameEngine.cpp

    include/ui/UI.h
    src/ui/UI.cpp

    include/states/GameStateManager.h
    src/states/GameStateManager.cpp

    include/states/State.h

    include/states/MainMenuState.h
    src/states/MainMenuState.cpp

    include/states/SettingsState.h
    src/states/SettingsState.cpp

    include/states/GameplayState.h
    src/states/GameplayState.cpp

    include/states/PauseState.h
    src/states/PauseState.cpp

    include/states/GameOverState.h
    src/states/GameOverState.cpp

    include/strategy/AIAlgorithmStrategy.h

    include/core/Settings.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ga MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    if(ANDROID)
        add_library(ga SHARED ${PROJECT_SOURCES})
    else()
        add_executable(ga ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(ga PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ga)
endif()

set_target_properties(ga PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)
install(TARGETS ga
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ga)
endif()
