set(CMAKE_INCLUDE_CURRENT_DIR ON) #required for include repc generates headers
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick RemoteObjects)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(RemoteObjectsClient
    main.cpp
)

qt_add_qml_module(RemoteObjectsClient
    URI RemoteObjects
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES Client.hpp
        SOURCES Client.cpp
)

qt6_add_repc_replicas(RemoteObjectsClient
    servercontroller.rep
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(RemoteObjectsClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RemoteObjectsClient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(RemoteObjectsClient
    PRIVATE Qt6::Quick
    Qt6::RemoteObjects
)

include(GNUInstallDirs)
install(TARGETS RemoteObjectsClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
