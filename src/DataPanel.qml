import QtQuick
import Qt.labs.folderlistmodel
import QtQuick.Controls

Rectangle {
    id: root
    property bool hidden: false
    property int baseMargin: 10

    function toggleHide() {
        if (root.hidden) {
            dataPanelAnimation.from = root.x
            dataPanelAnimation.to = 0
        } else {
            dataPanelAnimation.from = root.x
            dataPanelAnimation.to = -root.width
        }
        root.hidden = !root.hidden
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

    Button {
        id: newPartButton
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: root.baseMargin * 3
        anchors.topMargin: 10
        text: qsTr("New component")
        onClicked: newPartDialog.open()
    }

    ListView {
        id: partsListView
        spacing: 10
        anchors.top: newPartButton.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        topMargin: spacing
        model: folderModel

        FolderListModel {
            id: folderModel
            showDirs: true
            showFiles: true
            showHidden: true
            folder: backend.workspaceLocation
        }

        delegate: ItemDelegate {
            id: delegate
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: partsListView.width - partsListView.spacing * 2
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

    NewComponentDialog {
        id: newPartDialog

        x: root.parent.width / 2 - width / 2
        y: root.parent.height / 2 - height / 2

        onFinished: function (componentName) {
            backend.createNewComponent(componentName)
        }
    }
}
