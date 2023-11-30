cmake_minimum_required(VERSION 3.5)

if (MSVC)
    # Specify MSVC UTF-8 encoding
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

project(
    QtNote
    VERSION 1.0.0
    DESCRIPTION "qtnote project"
    LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/Qt/6.5.1/msvc2019_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")
set(QRC ./qtnote.qrc)
aux_source_directory(./src SRC)

if (MSVC)
    set(BUILD_DEFINE
        -D_AMD64_
        -DWIN32_LEAN_AND_MEAN
        -DUNICODE
    )
else()
    set(BUILD_DEFINE
        -DOBJC_OLD_DISPATCH_PROTOTYPES
    )
endif()
add_definitions(${BUILD_DEFINE})

set(PROJECT_OUTPUT ${CMAKE_SOURCE_DIR}/cmake/setoutput.cmake)
include(${PROJECT_OUTPUT})

# set(PROJECT_LINKDIR
#     "${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}"
# )
# if (MSVC)
#     list(APPEND PROJECT_LINKDIR
#         "${CMAKE_SOURCE_DIR}/lib/x64/"
#         "${CMAKE_SOURCE_DIR}/lib/x64/${CMAKE_BUILD_TYPE}"
#     )
# else()
#     list(APPEND PROJECT_LINKDIR
#     )
# endif()
# link_directories(${PROJECT_LINKDIR})

find_package(Qt6 COMPONENTS Widgets REQUIRED)
add_executable(${PROJECT_NAME}
    # WIN32 # If you need a terminal for debug, please comment this statement
    ${QRC}
    ${SRC}
)

add_subdirectory(acore)
add_subdirectory(awidget)
add_subdirectory(agui)
add_subdirectory(imagekit)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets AWidget ACore AGui)

