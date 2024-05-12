import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
//import QtQuick.Controls.Universal
//import QtQuick.Controls.Material
import QtCore
import QtQuick3D
import QtQuick3D.Helpers
import Flex3D.Editors.SimpleEditor 1.0
import Flex3D.Editors.AceSampleWebEngineEditor 1.0
import Flex3D.Editors.AceSampleWebViewEditor 1.0
import Flex3D.Editors.AceWebViewEditor 1.0
import Flex3D.Editors.BaseEditor 1.0
import Flex3D.FileIO 1.0

ApplicationWindow {
    title: qsTr("Flex 3D")
    visible: true
    visibility: "Maximized"
    width: 1280
    height: 800
    x: 0
    y: 0

    //Universal.theme: Universal.Dark
    //Material.theme: Material.Dark
    Component.onCompleted: {
        editorSplitView.restoreState(appSettings.editorSplitView)
    }
    Component.onDestruction: {
        appSettings.editorSplitView = editorSplitView.saveState()
    }

    Settings {
        id: appSettings
        property var editorSplitView
    }

    SplitView {
        id: editorSplitView
        anchors.fill: parent
        orientation: Qt.Horizontal

        ColumnLayout {
            id: pathLayout
            SplitView.preferredWidth: 400
            Row {
                Layout.fillHeight: false
                spacing: 5
                Button {
                    text: "Save"
                    onClicked: {
                        pathEdit.save()
                    }
                }
                Button {
                    text: "Format"
                    onClicked: {
                        pathEdit.format()
                    }
                }
                Button {
                    text: "Run"
                    onClicked: {
                        pathEdit.run()
                    }
                }
                Button {
                    text: "Run & Save"
                    onClicked: {
                        pathEdit.run_and_save()
                    }
                }
            }

            AceWebViewEditor {
                id: pathEdit
                property string fileName: "TestComponent.qml"
                property string fileDir: SOURCE_DIR + "/develop_project/"
                property FileIO file: FileIO {}
                Layout.fillHeight: true
                Layout.fillWidth: true

                onEditorReady: {
                    pathEdit.setText(file.readFile(fileDir, fileName))
                    //run()
                }

                function save() {
                    pathEdit.requestText(function (editorText) {
                        file.saveFile(fileDir, fileName, editorText)
                    })
                }

                function run_and_save() {
                    pathEdit.requestText(function (editorText) {
                        file.saveFile(fileDir, fileName, editorText)
                        cadView3D.run(editorText)
                    })
                }

                function run() {
                    pathEdit.requestText(function (editorText) {
                        cadView3D.run(editorText)
                    })
                }

                Shortcut {
                    sequence: "Ctrl+S"
                    onActivated: pathEdit.run()
                }
            }
        }

        CadView3D {
            id: cadView3D
            Layout.fillHeight: true
            Layout.fillWidth: true

            Node {
                id: embedNode
                property var userNode: null
            }

            function run(textComponent) {
                if (embedNode.userNode) {
                    embedNode.userNode.destroy()
                }
                embedNode.userNode = Qt.createQmlObject(textComponent,
                                                        embedNode, "userNode")
                embedNode.userNode.gui.parent = cadView3D
            }
        }
    }
}
