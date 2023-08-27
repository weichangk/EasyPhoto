cmake_minimum_required(VERSION 3.5)
project(QtNote LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/Qt/6.5.0/msvc2019_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")
find_package(Qt6 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS
set(qrcs ./QtNote.qrc)
aux_source_directory(./src srcs)
set(awidget_headers
    ./awidget/awidget.h
    ./awidget/awlistview.h
)
set(awidget_sources
    ./awidget/awidget.cpp
    ./awidget/awlistview.cpp
)
# Specify MSVC UTF-8 encoding
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# set(LOG_LEVEL "WARNING" CACHE STRING "Set the log level: DEBUG, INFO, WARNING, CRITICAL, or FATAL")
# add_compile_definitions(LOG_LEVEL=${LOG_LEVEL})

add_executable(${PROJECT_NAME}
    # WIN32 # If you need a terminal for debug, please comment this statement
    ${qrcs}
    ${srcs}
    ${awidget_headers}
    ${awidget_sources}
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
