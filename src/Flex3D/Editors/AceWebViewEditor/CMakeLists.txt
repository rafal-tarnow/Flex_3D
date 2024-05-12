set(mod_resource_files
    page/ide.html
    page/css/style.css
    page/js/ide.js
)

file(GLOB_RECURSE ace_files
    "page/js/lib/*"
)

qt_add_qml_module(AceWebViewEditor
    URI Flex3D.Editors.AceWebViewEditor
    VERSION 1.0
    QML_FILES
        AceWebViewEditor.qml
    # RESOURCES
    #     ${mod_resource_files}
    # RESOURCE_PREFIX "/qt/qml"
)



qt_add_resources(AceWebViewEditor "page"
    PREFIX
        "/"
    BASE
        "page"
    FILES
        ${mod_resource_files}
    FILES
        ${ace_files}
)
