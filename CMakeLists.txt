cmake_minimum_required(VERSION 3.21)

project(qfluentwidgets
    VERSION 0.1.0
    DESCRIPTION "Qt Fluent Widgets for C++"
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(QFLUENTWIDGETS_BUILD_EXAMPLES "Build demo/test executables" OFF)
option(QFLUENTWIDGETS_BUILD_SHARED "Build qfluentwidgets as a shared library" ON)
option(QFLUENTWIDGETS_BUILD_MULTIMEDIA "Build qfluentwidgets media player components" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTORCC_OPTIONS "--compress-algo=none")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg Xml)
if(QFLUENTWIDGETS_BUILD_MULTIMEDIA)
    find_package(Qt6 REQUIRED COMPONENTS Multimedia MultimediaWidgets)
endif()
find_package(jsoncpp CONFIG REQUIRED)

if(TARGET JsonCpp::JsonCpp)
    set(QFLUENTWIDGETS_JSONCPP_TARGET JsonCpp::JsonCpp)
else()
    set(QFLUENTWIDGETS_JSONCPP_TARGET jsoncpp_lib)
endif()

file(GLOB_RECURSE QFLUENTWIDGETS_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/common/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/components/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/qframelesswindow/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/window/*.h"
)

file(GLOB_RECURSE QFLUENTWIDGETS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/common/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/components/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/qframelesswindow/titlebar/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/window/*.cpp"
)

if(QFLUENTWIDGETS_BUILD_MULTIMEDIA)
    file(GLOB_RECURSE QFLUENTWIDGETS_MULTIMEDIA_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/multimedia/*.h"
    )
    file(GLOB_RECURSE QFLUENTWIDGETS_MULTIMEDIA_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/multimedia/*.cpp"
    )
    list(APPEND QFLUENTWIDGETS_HEADERS ${QFLUENTWIDGETS_MULTIMEDIA_HEADERS})
    list(APPEND QFLUENTWIDGETS_SOURCES ${QFLUENTWIDGETS_MULTIMEDIA_SOURCES})
endif()

list(APPEND QFLUENTWIDGETS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/_rc/resource.qrc"
)

if(WIN32)
    file(GLOB QFLUENTWIDGETS_PLATFORM_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/qframelesswindow/windows/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/qframelesswindow/utils/*.cpp"
    )
    list(REMOVE_ITEM QFLUENTWIDGETS_PLATFORM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/qframelesswindow/windows/qframe_less_window_stub.cpp"
    )
else()
    set(QFLUENTWIDGETS_PLATFORM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/qframelesswindow/windows/qframe_less_window_stub.cpp"
    )
endif()

if(QFLUENTWIDGETS_BUILD_SHARED)
    set(QFLUENTWIDGETS_LIBRARY_TYPE SHARED)
else()
    set(QFLUENTWIDGETS_LIBRARY_TYPE STATIC)
endif()

add_library(qfluentwidgets ${QFLUENTWIDGETS_LIBRARY_TYPE}
    ${QFLUENTWIDGETS_HEADERS}
    ${QFLUENTWIDGETS_SOURCES}
    ${QFLUENTWIDGETS_PLATFORM_SOURCES}
)

add_library(qfluentwidgets::qfluentwidgets ALIAS qfluentwidgets)

target_include_directories(qfluentwidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(qfluentwidgets
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Svg
        Qt6::Xml
        ${QFLUENTWIDGETS_JSONCPP_TARGET}
)

if(QFLUENTWIDGETS_BUILD_MULTIMEDIA)
    target_link_libraries(qfluentwidgets PUBLIC Qt6::Multimedia Qt6::MultimediaWidgets)
endif()

target_compile_definitions(qfluentwidgets
    PRIVATE
        QFLUENTWIDGETS_LIBRARY
)

if(MSVC)
    # Qt6 requires /Zc:__cplusplus for correct __cplusplus macro reporting
    target_compile_options(qfluentwidgets PRIVATE "/Zc:__cplusplus")
endif()

if(WIN32 AND QFLUENTWIDGETS_BUILD_SHARED)
    target_compile_definitions(qfluentwidgets
        PRIVATE QFLUENTWIDGETS_EXPORT=__declspec\(dllexport\)
        INTERFACE QFLUENTWIDGETS_EXPORT=__declspec\(dllimport\)
    )
else()
    target_compile_definitions(qfluentwidgets PUBLIC QFLUENTWIDGETS_EXPORT=)
endif()

set_target_properties(qfluentwidgets PROPERTIES
    OUTPUT_NAME qfluentwidgets
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

if(WIN32)
    target_link_libraries(qfluentwidgets PUBLIC Dwmapi User32 Gdi32)
endif()

install(TARGETS qfluentwidgets
    EXPORT qfluentwidgetsTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY qfluentwidgets/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qfluentwidgets
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.qrc" EXCLUDE
        PATTERN "_rc" EXCLUDE
        PATTERN "test" EXCLUDE
)

install(EXPORT qfluentwidgetsTargets
    FILE qfluentwidgetsTargets.cmake
    NAMESPACE qfluentwidgets::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qfluentwidgets
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/qfluentwidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/qfluentwidgetsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qfluentwidgets
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/qfluentwidgetsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/qfluentwidgetsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/qfluentwidgetsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qfluentwidgets
)

if(QFLUENTWIDGETS_BUILD_EXAMPLES)
    file(GLOB QFLUENTWIDGETS_EXAMPLE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/*_test.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/gallery_test.cpp"
    )
    list(REMOVE_ITEM QFLUENTWIDGETS_EXAMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/acrylic_combo_box_test.cpp"
    )

    file(GLOB_RECURSE QFLUENTWIDGETS_GALLERY_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/gallery/*.cpp"
    )

    add_custom_target(qfluentwidgets_examples)
    set(QFLUENTWIDGETS_DEPLOY_COMMANDS)
    if(WIN32)
        find_program(QFLUENTWIDGETS_WINDEPLOYQT_EXECUTABLE
            NAMES windeployqt
            HINTS "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/tools/Qt6/bin"
        )
    endif()

    foreach(example_source IN LISTS QFLUENTWIDGETS_EXAMPLE_SOURCES)
        get_filename_component(example_name "${example_source}" NAME_WE)
        add_executable("${example_name}" "${example_source}")
        target_link_libraries("${example_name}" PRIVATE qfluentwidgets::qfluentwidgets)
        target_include_directories("${example_name}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
        add_dependencies(qfluentwidgets_examples "${example_name}")
        set_target_properties("${example_name}" PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
        )

        if(WIN32 AND QFLUENTWIDGETS_BUILD_SHARED)
            add_custom_command(TARGET "${example_name}" POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "$<TARGET_FILE:qfluentwidgets>"
                    "$<TARGET_FILE_DIR:${example_name}>"
                COMMENT "Copying qfluentwidgets runtime library for ${example_name}"
            )
        endif()

        if(QFLUENTWIDGETS_WINDEPLOYQT_EXECUTABLE)
            list(APPEND QFLUENTWIDGETS_DEPLOY_COMMANDS
                COMMAND "${QFLUENTWIDGETS_WINDEPLOYQT_EXECUTABLE}"
                    --release
                    --no-translations
                    "$<TARGET_FILE:${example_name}>"
            )
        endif()

        if(example_name STREQUAL "gallery_test")
            target_sources("${example_name}" PRIVATE ${QFLUENTWIDGETS_GALLERY_SOURCES})
        endif()

        if(example_name STREQUAL "setting_test")
            target_sources("${example_name}" PRIVATE
                "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/settings_test/setting_config.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/settings_test/setting_interface.cpp"
            )
        endif()

        if(example_name STREQUAL "login_window_test")
            target_sources("${example_name}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/qfluentwidgets/test/login_window.cpp")
        endif()
    endforeach()

    if(QFLUENTWIDGETS_WINDEPLOYQT_EXECUTABLE)
        add_custom_target(qfluentwidgets_deploy_examples
            ${QFLUENTWIDGETS_DEPLOY_COMMANDS}
            DEPENDS qfluentwidgets_examples
            COMMENT "Deploying Qt runtime files for qfluentwidgets examples"
        )
    endif()
endif()
