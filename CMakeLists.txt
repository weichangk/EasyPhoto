cmake_minimum_required(VERSION 3.16)

project(
    ImageKit
    VERSION 1.0.0
    DESCRIPTION "imagekit project"
    LANGUAGES CXX
)

include(${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial/cmake/public.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial)

MY_ADD_PROJECT_INCLUDE_FUNC(
    ${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial/inc
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/include
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/include/Magick++
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/include/MagickCore
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/include/MagickWand
)

MY_ADD_QT_PACK_FUNC(
    Widgets
)

MY_ADD_LINK_LIB_FUNC(
    QtMaterial
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/lib/CORE_DB_Magick++_.lib
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/lib/CORE_DB_MagickCore_.lib
    ${CMAKE_SOURCE_DIR}/3rdparty/magick/lib/CORE_DB_MagickWand_.lib
)

include(${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial/cmake/option.cmake)
include(${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial/cmake/code.cmake)
include(${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial/cmake/exe.cmake)
include(${CMAKE_SOURCE_DIR}/3rdparty/QtMaterial/cmake/link.cmake)

include(config.cmake)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_ID}")

target_compile_definitions(${PROJECT_NAME} PRIVATE
    APPLICATION_ID="${PROJECT_ID}"
    APPLICATION_DISPLAY_NAME="${PROJECT_NAME}"
    APPLICATION_DESCRIPTION="${PROJECT_DESCRIPTION}"
    APPLICATION_ORGANIZATION_DOMAIN="${PROJECT_ORGANIZATION_URL}"
    APPLICATION_ORGANIZATION_NAME="${PROJECT_ORGANIZATION_NAME}"
    APPLICATION_DATA_DIR="${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_ID}"
    APPLICATION_ICON_NAME="${PROJECT_ICON_FILE_NAME}"
    APPLICATION_ICON_SYSTEM_PATH="${PROJECT_ICON_FILE_PATH}/${PROJECT_ICON_FILE_NAME}"
)
