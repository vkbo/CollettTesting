cmake_minimum_required(VERSION 3.5)

project(Collett LANGUAGES CXX VERSION "0.4.4")
set(Collett_VERSION_DATE "2020-02-14")
configure_file(src/collett.h src/collett.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -g -O0 ${CMAKE_CXX_FLAGS_DEBUG}")

find_package(Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)

# set(TS_FILES Collett_en_GB.ts)

include_directories(
    src
    src/gui
    src/gui/elements
    src/core
)

add_executable(collett
    src/collett.h
    src/main.cpp
    src/config.h
    src/config.cpp
    src/guimain.h
    src/guimain.cpp
    src/gui/mainmenu.h
    src/gui/mainmenu.cpp
    src/gui/statusbar.h
    src/gui/statusbar.cpp
    src/gui/elements/docdetails.h
    src/gui/elements/docdetails.cpp
    src/gui/elements/doceditor.h
    src/gui/elements/doceditor.cpp
    src/gui/elements/doctree.h
    src/gui/elements/doctree.cpp
    src/gui/elements/docviewer.h
    src/gui/elements/docviewer.cpp
    src/gui/elements/noticebar.h
    src/gui/elements/noticebar.cpp
    src/gui/elements/searchbar.h
    src/gui/elements/searchbar.cpp
    src/gui/elements/viewdetails.h
    src/gui/elements/viewdetails.cpp
    # ${TS_FILES}
)

add_library(CollettCore STATIC
    src/core/project.h
    src/core/project.cpp
    src/core/item.h
    src/core/item.cpp
)

target_link_libraries(CollettCore PRIVATE Qt5::Core)
target_link_libraries(collett     PRIVATE Qt5::Widgets CollettCore)

# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
