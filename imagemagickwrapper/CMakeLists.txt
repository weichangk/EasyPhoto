cmake_minimum_required(VERSION 3.5)

if (MSVC)
    # Specify MSVC UTF-8 encoding
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

project(
    ImageMagickWrapper
    VERSION 1.0.0
    DESCRIPTION "imagemagickwrapper static library project"
    LANGUAGES CXX)

if (MSVC)
    set(BUILD_DEFINE
        -DIMAGEMAGICKWRAPPER_LIB
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

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE INC "inc/*.h" "inc/*.hpp")
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.cc")

add_library(${PROJECT_NAME} SHARED
    ${INC}
    ${SRC}
)

include_directories(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/include
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/include/Magick++
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/include/MagickCore
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/include/MagickWand
)

link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/lib/CORE_RL_Magick++_.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/lib/CORE_RL_MagickCore_.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/magick/lib/CORE_RL_MagickWand_.lib
)

