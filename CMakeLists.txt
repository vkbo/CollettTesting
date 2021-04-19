cmake_minimum_required(VERSION 3.5)

project(Collett LANGUAGES CXX VERSION "0.0.1")
set(Collett_VERSION_DATE "2020-12-17")
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

# Source Files
list(APPEND SRC_CORE
    item
    project
    projxmlreader
)
list(APPEND SRC_BASE
    main
    config
    guimain
)
list(APPEND SRC_GUI
    elements/docdetails
    elements/doceditor
    elements/doctree
    elements/docviewer
    elements/noticebar
    elements/searchbar
    elements/viewdetails
    mainmenu
    statusbar
)

include_directories(
    src
    src/gui
    src/gui/elements
    src/core
)

# Source Files for libCollettCore

foreach(entry IN LISTS SRC_CORE)
    list(APPEND LIB_CORE_SRC src/core/${entry}.cpp)
endforeach()

# Source Files for Main Exec

foreach(entry IN LISTS SRC_BASE)
    list(APPEND EXEC_SRC src/${entry}.cpp)
endforeach()
foreach(entry IN LISTS SRC_GUI)
    list(APPEND EXEC_SRC src/gui/${entry}.cpp)
endforeach()
# list(APPPEND EXEC_SRC ${TS_FILES})

# Add Sources to Targets
add_executable(collett ${EXEC_SRC})
add_library(CollettCore STATIC ${LIB_CORE_SRC})

target_link_libraries(CollettCore PRIVATE Qt5::Core)
target_link_libraries(collett     PRIVATE Qt5::Widgets CollettCore)

# qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
