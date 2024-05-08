import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import QtQuick3D
//import QtWebView
import Flex3D.Editors.SimpleEditor 1.0
import Flex3D.Editors.AceSampleWebEngineEditor 1.0
import Flex3D.Editors.AceSampleWebViewEditor 1.0
import Flex3D.Editors.AceWebViewEditor 1.0
import Flex3D.Editors.BaseEditor 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Flex 3D")

    property var exampleCode: `
    import QtQuick 2.7
    import QtQuick.Controls 2.3
    Rectangle {
    color: "red"
    anchors.fill: parent
    Text {
    text: "WEEEEEEEEEE"
    font.pixelSize: 50
    color: "white"
    anchors.centerIn: parent
    RotationAnimator on rotation {
    running: true
    loops: Animation.Infinite
    from: 0
    to: 360
    duration: 700
    }
    }
    }`

    Component.onCompleted:{
        editorSplitView.restoreState(appSettings.editorSplitView);
    }
    Component.onDestruction:{
        appSettings.editorSplitView = editorSplitView.saveState();
    }

    Settings {
        id: appSettings
        property alias code: pathEdit.text
        property var editorSplitView
    }

    SplitView {
        id: editorSplitView
        anchors.fill: parent
        orientation: Qt.Horizontal

        ColumnLayout {
            id: pathLayout
            SplitView.preferredWidth: 400
            AceWebViewEditor {
                id: pathEdit
                text: exampleCode
                Layout.fillHeight: true
                Layout.fillWidth: true
                onEditingFinished: updateItem()
                Component.onCompleted: {
                    updateItem()
                }
                function updateItem() {
                    userParentItem.create(pathEdit.text)
                }

                Shortcut {
                    sequence: "Ctrl+S"
                    onActivated: pathEdit.updateItem()
                }
            }
            Button {
                id: pathEditButton
                Layout.fillWidth: true
                text: "ok!"
                onClicked: pathEdit.updateItem()
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

    // WebEngineView {
    //     x: 0
    //     y: 0
    //     z: 2
    //     width: 400
    //     height: 400
    //     url: "https://ace.c9.io/build/kitchen-sink.html"
    // }

    // WebView {
    //     x: 0
    //     y: 0
    //     z: 2
    //     width: 400
    //     height: 400
    //     url: "https://ace.c9.io/build/kitchen-sink.html"
    // }
}
