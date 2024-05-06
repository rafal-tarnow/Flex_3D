cmake_minimum_required(VERSION 3.16)

project(Flex3D VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Quick3D WebView Positioning WebChannel)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appFlex3D
    main.cpp
)

qt_add_qml_module(appFlex3D
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
set_target_properties(appFlex3D PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFlex3D
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFlex3D PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Quick3D
    Qt6::WebView
    Qt6::Positioning
    Qt6::WebChannel
)

include(GNUInstallDirs)
install(TARGETS appFlex3D
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
