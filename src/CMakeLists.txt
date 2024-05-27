cmake_minimum_required(VERSION 3.16)

project(Flex3D-app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Qt6 REQUIRED COMPONENTS Core QuickControls2 Quick3D WebEngineQuick WebView)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${PROJECT_NAME}
    main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI Flex3D
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES BodyCube.qml
    QML_FILES FBody.qml
    QML_FILES OriginGizmo.qml
    QML_FILES CadView3D.qml
    SOURCES Backend.hpp
    SOURCES Backend.cpp
    SOURCES FileIO.hpp
    SOURCES FileIO.cpp
    QML_FILES DataPanel.qml
    QML_FILES NewComponentDialog.qml
    SOURCES ScadNode.hpp
    SOURCES ScadNode.cpp
)

qt_add_resources(${PROJECT_NAME} "testRect"
    PREFIX
        "/"
    BASE
        "."
    FILES
        resources/ComponentTemplate.qml
        resources/ComponentTemplate.scad

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFlex3D
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::QuickControls2
    Qt6::Quick3D
    Qt6::WebView
    Qt6::WebEngineQuick
    Qt6::Quick3DPrivate
    #Qt${QT_VERSION_MAJOR}::WidgetsPrivate
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(Flex3D/Editors/SimpleEditor/)
add_subdirectory(Flex3D/Editors/AceWebViewEditor/)
add_subdirectory(Flex3D/Editors/AceSampleWebEngineEditor/)
add_subdirectory(Flex3D/Editors/AceSampleWebViewEditor/)
add_subdirectory(Flex3D/Editors/BaseEditor/)
add_subdirectory(Flex3D/FProcess/)
add_subdirectory(Flex3D/Cad/)
