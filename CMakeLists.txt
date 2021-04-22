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

# Source Files
list(APPEND SRC_CORE
    item
    project
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
qt6_add_executable(collett ${EXEC_SRC} ${TS_FILES})
add_library(CollettCore STATIC ${LIB_CORE_SRC})

target_link_libraries(CollettCore PRIVATE Qt6::Core)
target_link_libraries(collett     PRIVATE Qt6::Widgets CollettCore)

qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
