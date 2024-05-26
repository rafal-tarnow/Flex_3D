cmake_minimum_required(VERSION 3.5)

project(SharedMemory VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")


find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets Widgets)

set(PROJECT_COMMON_SOURCES
    config.hpp
)

set(PROJECT_SERVER_SOURCES
    server/main_server.cpp
    server/TriangleWidget.h
    server/TriangleWidget.cpp
)

set(PROJECT_CLIENT_SOURCES
    client/main_client.cpp
    client/ClientWidget.hpp
    client/ClientWidget.cpp
)

qt_add_executable(SharedMemoryServer
    MANUAL_FINALIZATION
    ${PROJECT_SERVER_SOURCES}
    ${PROJECT_COMMON_SOURCES}
)

qt_add_executable(SharedMemoryClient
    MANUAL_FINALIZATION
    ${PROJECT_CLIENT_SOURCES}
    ${PROJECT_COMMON_SOURCES}
)


target_link_libraries(SharedMemoryServer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
target_link_libraries(SharedMemoryClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  )

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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SharedMemoryServer)
    qt_finalize_executable(SharedMemoryClient)
endif()
