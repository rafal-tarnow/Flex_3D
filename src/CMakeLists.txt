cmake_minimum_required(VERSION 3.16)

project(Flex3D-app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Quick3D WebEngineQuick WebView)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${PROJECT_NAME}
    main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI Flex3D
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES CadScene.qml
    QML_FILES BodyCube.qml
    QML_FILES Body.qml
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
    Qt6::Quick
    Qt6::Quick3D
    Qt6::WebView
    Qt6::WebEngineQuick
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
