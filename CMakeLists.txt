cmake_minimum_required(VERSION 3.5)

project(Collett LANGUAGES CXX VERSION "0.0.1")
set(Collett_VERSION_DATE "2020-12-17")
configure_file(src/collett.h src/collett.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -g -O0 ${CMAKE_CXX_FLAGS_DEBUG}")

# Qt6
# ===

# Just symlink lib/qt6 to the correct location,
# or set the path with -DCMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "lib/qt6")

set(QT_DEFAULT_MAJOR_VERSION 6)
set(QT_NO_CREATE_VERSIONLESS_FUNCTIONS on)
set(QT_NO_CREATE_VERSIONLESS_TARGETS on)

find_package(Qt6 COMPONENTS Core Widgets LinguistTools REQUIRED)
if(Qt6Widgets_FOUND)
    message(STATUS "Found Qt6 Version: ${Qt6Widgets_VERSION}")
    message(STATUS "Found Qt6 Libraries: ${Qt6Widgets_LIBRARIES}")
endif()

# i18n
# ====

set(TS_FILES
    i18n/collett_en_US.ts
    i18n/collett_nb_NO.ts
)

# Sources
# =======

# Source Folders
include_directories(
    src
    src/document
    src/editor
    src/gui
    src/project
)

# Source Files
list(APPEND Collet_SOURCE
    document/collettdocparser
    document/document
    document/linefmt
    editor/doceditor
    editor/docexporter
    editor/docimporter
    gui/mainmenu
    gui/noveltree
    gui/statusbar
    project/item
    project/project
    data
    guimain
    main
    settings
)

foreach(entry IN LISTS Collet_SOURCE)
    list(APPEND EXEC_SRC src/${entry}.cpp)
endforeach()

# Targets
# =======

qt6_add_executable(collett ${EXEC_SRC} ${TS_FILES})
target_link_libraries(collett PRIVATE Qt6::Widgets)

qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
