cmake_minimum_required(VERSION 3.16)

project(SharedMemory_02 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# Determine the Qt version
find_package(Qt6 QUIET COMPONENTS Core QuickControls2 Gui OpenGL OpenGLWidgets Widgets)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    set(QT_PACKAGE_PREFIX Qt6)
    qt_standard_project_setup(REQUIRES 6.5)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core QuickControls2 Gui OpenGL Widgets)
    set(QT_VERSION_MAJOR 5)
    set(QT_PACKAGE_PREFIX Qt5)
endif()

set(PROJECT_COMMON_SOURCES
    config.hpp
)

set(PROJECT_SERVER_SOURCES
    server/main_server.cpp
    server/TriangleWidget.h
    server/TriangleWidget.cpp
)

# Use the appropriate qt_add_executable function based on the Qt version
if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(SharedMemoryServer
        MANUAL_FINALIZATION
        ${PROJECT_SERVER_SOURCES}
        ${PROJECT_COMMON_SOURCES}
    )
else()
    add_executable(SharedMemoryServer
        ${PROJECT_SERVER_SOURCES}
        ${PROJECT_COMMON_SOURCES}
    )
endif()

set(PROJECT_CLIENT_SOURCES
    client/main_client.cpp
    client/ClientWidget.hpp
    client/ClientWidget.cpp
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(SharedMemoryClient
        MANUAL_FINALIZATION
        ${PROJECT_CLIENT_SOURCES}
        ${PROJECT_COMMON_SOURCES}
    )
else()
    add_executable(SharedMemoryClient
        ${PROJECT_CLIENT_SOURCES}
        ${PROJECT_COMMON_SOURCES}
    )
endif()

# qt_add_resources(SharedMemoryClient "testRect"
#     PREFIX
#         "/"
#     BASE
#         "."
#     FILES
#         client/Main.qml
# )

if(Qt6_FOUND)
    target_link_libraries(SharedMemoryServer PRIVATE
        ${QT_PACKAGE_PREFIX}::Widgets
        ${QT_PACKAGE_PREFIX}::OpenGL
        ${QT_PACKAGE_PREFIX}::OpenGLWidgets
    )
else()
    target_link_libraries(SharedMemoryServer PRIVATE
        ${QT_PACKAGE_PREFIX}::Widgets
        ${QT_PACKAGE_PREFIX}::OpenGL
    )
endif()
target_link_libraries(SharedMemoryClient PRIVATE
    ${QT_PACKAGE_PREFIX}::Widgets
    ${QT_PACKAGE_PREFIX}::QuickControls2
)

set_target_properties(SharedMemoryServer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_target_properties(SharedMemoryClient PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SharedMemoryServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS SharedMemoryClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executables if using Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SharedMemoryServer)
    qt_finalize_executable(SharedMemoryClient)
endif()
