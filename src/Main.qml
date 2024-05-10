import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import QtQuick3D
import Flex3D.Editors.SimpleEditor 1.0
import Flex3D.Editors.AceSampleWebEngineEditor 1.0
import Flex3D.Editors.AceSampleWebViewEditor 1.0
import Flex3D.Editors.AceWebViewEditor 1.0
import Flex3D.Editors.BaseEditor 1.0

ApplicationWindow {
    title: qsTr("Flex 3D")
    visible: true
    visibility: "Maximized"
    width: 1280
    height: 800
    x: 0
    y: 0

    Component.onCompleted: {
        editorSplitView.restoreState(appSettings.editorSplitView)
    }
    Component.onDestruction: {
        appSettings.editorSplitView = editorSplitView.saveState()
    }

    Settings {
        id: appSettings
        property string code
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
            }

            AceWebViewEditor {
                id: pathEdit
                Layout.fillHeight: true
                Layout.fillWidth: true
                onEditingFinished: run()
                Component.onCompleted: {
                    text = appSettings.code
                    run()
                }
                function save() {
                    pathEdit.requestText(function (editorText) {
                        appSettings.code = editorText
                    })
                }

                function run() {
                    pathEdit.requestText(function (editorText) {
                        userParentItem.create(editorText)
                        appSettings.code = editorText
                    })
                }

                Shortcut {
                    sequence: "Ctrl+S"
                    onActivated: pathEdit.run()
                }
            }
        }

        CadScene {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Item {
                id: userParentItem
                width: 300
                height: 300
                property var userItem: null

                function create(textComponent) {
                    if (userItem) {
                        userItem.destroy()
                    }
                    userItem = Qt.createQmlObject(textComponent,
                                                  userParentItem, "userItem")
                }
            }
        }
    }
}
