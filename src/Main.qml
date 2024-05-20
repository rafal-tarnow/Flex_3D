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
import Flex3D.FProcess 1.0

ApplicationWindow {
    title: qsTr("Flex 3D")
    visible: true
    //visibility: "Maximized"
    width: Screen.width * 0.95
    height: Screen.height * 0.75
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

    DataPanel {
        id: dataPanel
        height: parent.height
        width: 400
        hidden: false
    }

    SplitView {
        id: editorSplitView

        x: dataPanel.x + dataPanel.width
        width: parent.width - x
        height: parent.height

        orientation: Qt.Horizontal

        ColumnLayout {
            id: pathLayout
            SplitView.preferredWidth: 400
            Row {
                Layout.fillHeight: false
                spacing: 5

                RoundButton {
                    id: dataPanelButton
                    text: "\u2630" // Unicode Character 'TRIGRAM FOR HEAVEN', no qsTr()
                    onClicked: {
                        dataPanel.toggleHide()
                        dataPanelButton.state = "rotated"
                    }
                    height: saveButton.height
                    width: height
                }

                Button {
                    id: saveButton
                    text: "Save"
                    onClicked: {
                        editor.save()
                    }
                }
                Button {
                    text: "Format"
                    onClicked: {
                        editor.format()
                    }
                }
                Button {
                    text: "Run & Save"
                    onClicked: {
                        editor.run_and_save()
                    }
                }
                Button {
                    text: "balsamui.exe"
                    onClicked: {
                        balsamui.start()
                    }
                    FProcess {
                        id: balsamui
                        program: "C:/Qt_6_7_0/6.7.0/msvc2019_64/bin/balsamui.exe"
                    }
                }
            }

            AceWebViewEditor {
                id: editor
                Layout.fillHeight: true
                Layout.fillWidth: true

                onEditorReady: {

                }

                function save() {
                    editor.requestText(function (editorText) {
                        backend.currentEditorFileText = editorText
                        backend.saveCurrentEditorFile()
                    })
                }

                function run_and_save() {
                    editor.requestText(function (editorText) {
                        backend.currentEditorFileText = editorText
                        backend.saveCurrentEditorFile()
                        cadView3D.run()
                    })
                }

                Shortcut {
                    sequence: "Ctrl+S"
                    onActivated: editor.run()
                }
            }
        }

        CadView3D {
            id: cadView3D

            function run() {
                partSource = ""
                partSource = backend.currentEditorFileUrl
            }

            onPartSourceChanged: {
                backend.clearEngineComponentCache()
            }

            Connections {
                target: backend
                function onCurrentEditorFileUrlChanged() {
                    editor.setText(backend.currentEditorFileText)
                    cadView3D.partSource = backend.currentEditorFileUrl
                }
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
