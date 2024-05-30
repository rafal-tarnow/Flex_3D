set(CMAKE_INCLUDE_CURRENT_DIR ON) #required for include repc generates headers
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick RemoteObjects)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(RemoteObjectsServer
    main.cpp
)

qt_add_qml_module(RemoteObjectsServer
    URI RemoteObjects
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES ServerController.hpp
        SOURCES ServerController.cpp
)

qt6_add_repc_sources(RemoteObjectsServer
    servercontroller.rep
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(RemoteObjectsServer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RemoteObjectsServer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(RemoteObjectsServer
    PRIVATE Qt6::Quick
    Qt6::RemoteObjects
)

include(GNUInstallDirs)
install(TARGETS RemoteObjectsServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
