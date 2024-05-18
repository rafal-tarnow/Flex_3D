import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
//import QtQuick.Controls.Universal
//import QtQuick.Controls.Material
import QtCore
import QtQuick3D
import QtQuick3D.Helpers
import Qt.labs.folderlistmodel
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

    Rectangle {
        id: dataPanel
        height: parent.height
        width: 400
        property bool hidden: false

        function toggleHide() {
            if (dataPanel.hidden) {
                dataPanelAnimation.from = dataPanel.x
                dataPanelAnimation.to = 0
            } else {
                dataPanelAnimation.from = dataPanel.x
                dataPanelAnimation.to = -dataPanel.width
            }
            dataPanel.hidden = !dataPanel.hidden
            dataPanelAnimation.running = true
        }

        NumberAnimation on x {
            id: dataPanelAnimation
            running: false
            from: width
            to: width
            duration: 100
        }

        color: "#f0f0f0"

        ListView {
            id: partsListView
            spacing: 10
            topMargin: spacing
            anchors.fill: parent
            model: folderModel

            FolderListModel {
                id: folderModel
                showDirs: true
                showFiles: true
                showHidden: true
                folder: "file:" + SOURCE_DIR + /develop_project/
            }

            delegate: ItemDelegate {
                id: delegate
                anchors.horizontalCenter: parent.horizontalCenter
                height: 50
                width: parent.width - partsListView.spacing * 2
                required property string fileName
                required property string filePath
                required property string fileBaseName
                required property string fileSuffix
                required property bool fileIsDir

                Rectangle {
                    id: fileDelegate
                    anchors.fill: parent
                    color: "white"

                    Text {
                        text: delegate.fileName
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: {
                        console.log("Double clicked item delegate !! youpi !!")
                        console.log("fileName = " + delegate.fileName)
                        console.log("filePath = " + delegate.filePath)
                        console.log("fileBaseName = " + delegate.fileBaseName)
                        console.log("fileSuffix = " + delegate.fileSuffix)
                        console.log("fileIsDir = " + delegate.fileIsDir)
                        if (delegate.fileIsDir === false
                                && delegate.fileSuffix === "qml") {
                            backend.currentEditorFileUrl = folderModel.folder + delegate.fileName
                        }
                    }
                }
            }
        }
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
                    text: "\u2630" // Unicode Character 'TRIGRAM FOR HEAVEN', no qsTr()
                    onClicked: dataPanel.toggleHide()
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

                Button {
                    text: "Set scene"
                    property bool selectedScene: false
                    onClicked: {
                        selectedScene = !selectedScene
                        if (selectedScene) {
                            cadView3D.partSource = "file:///" + SOURCE_DIR
                                    + "/develop_project/balsamui/Profile_8080.qml"
                        } else {
                            cadView3D.partSource = "file:///" + SOURCE_DIR
                                    + "/develop_project/TestComponent.qml"
                        }
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
