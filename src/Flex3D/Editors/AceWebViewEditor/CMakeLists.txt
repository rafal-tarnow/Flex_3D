qt_add_qml_module(AceWebViewEditor
    URI Flex3D.Editors.AceWebViewEditor
    VERSION 1.0
    QML_FILES
        AceWebViewEditor.qml
)

set(mod_resource_files
    "page/index.html"
    "page/change.js"
    "page/button/button.js"
)
qt_add_resources(AceWebViewEditor "page"
    PREFIX
        "/"
    BASE
        "page"
    FILES
        ${mod_resource_files}
)
