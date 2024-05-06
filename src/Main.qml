import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import QtQuick3D
import QtWebView

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

    // Settings {
    //     id: appSettings
    //     property alias code: pathEdit.text
    // }

    // SplitView {
    //     anchors.fill: parent
    //     orientation: Qt.Horizontal

    //     ColumnLayout {
    //         id: pathLayout
    //         Layout.fillHeight: true
    //         Layout.fillWidth: true
    //         TextEdit {
    //             id: pathEdit
    //             text: exampleCode
    //             Layout.fillHeight: true
    //             Layout.fillWidth: true
    //             onEditingFinished: updateItem()
    //             Component.onCompleted: {
    //                 updateItem()
    //             }
    //             function updateItem() {
    //                 userParentItem.create(pathEdit.text)
    //             }

    //             Shortcut {
    //                 sequence: "Ctrl+S"
    //                 onActivated: pathEdit.updateItem()
    //             }
    //         }
    //         Button {
    //             id: pathEditButton
    //             Layout.fillWidth: true
    //             text: "ok!"
    //             onClicked: pathEdit.updateItem()
    //         }
    //     }

    //     CadScene {
    //         Layout.fillHeight: true
    //         Layout.fillWidth: true

    //         Item {
    //             id: userParentItem
    //             width: 300
    //             height: 300
    //             property var userItem: null

    //             function create(textComponent) {
    //                 if (userItem) {
    //                     userItem.destroy()
    //                 }
    //                 userItem = Qt.createQmlObject(textComponent,
    //                                               userParentItem, "userItem")
    //             }
    //         }
    //     }
    // }
    WebView {
        id: webView
        x: 0
        y: 0
        z: 1
        width: 400
        height: 400
        url: "http://www.onet.pl"
    }
}
