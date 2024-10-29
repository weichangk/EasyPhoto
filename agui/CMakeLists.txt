cmake_minimum_required(VERSION 3.5)

if (MSVC)
    # Specify MSVC UTF-8 encoding
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

project(
    AGui
    VERSION 1.0.0
    DESCRIPTION "agui shared library project"
    LANGUAGES CXX
)

set(PROJECT_OUTPUT ${CMAKE_SOURCE_DIR}/cmake/setoutput.cmake)
include(${PROJECT_OUTPUT})

if (MSVC)
    set(BUILD_DEFINE
        -DAGUI_LIB
        -D_AMD64_
        -DWIN32_LEAN_AND_MEAN
        -DUNICODE
        -D_WINDOWS
        -D_UNICODE
        -DWIN32
        -DWIN64
    )
else()
    set(BUILD_DEFINE
        -DOBJC_OLD_DISPATCH_PROTOTYPES
    )
endif()
add_definitions(${BUILD_DEFINE})

set(CMAKE_PREFIX_PATH "d:/Qt/6.5.1/msvc2019_64") # Qt Kit Dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QRC ./agui.qrc)

set(PROJECT_LINKDIR
    "${CMAKE_SOURCE_DIR}/../${CMAKE_BUILD_TYPE}"
)
if (MSVC)
    list(APPEND PROJECT_LINKDIR
        "${CMAKE_SOURCE_DIR}/../lib/x64/"
        "${CMAKE_SOURCE_DIR}/../lib/x64/${CMAKE_BUILD_TYPE}"
    )
else()
    list(APPEND PROJECT_LINKDIR
    )
endif()
link_directories(${PROJECT_LINKDIR}) # 由于依赖其他模块，使单独构建能够通过

find_package(Qt5 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS

file(GLOB_RECURSE INC "inc/*.h" "inc/*.hpp")
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.cc")

add_library(${PROJECT_NAME} SHARED
    ${QRC}
    ${INC}
    ${SRC}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets AWidget)


