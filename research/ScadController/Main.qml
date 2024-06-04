import QtQuick
import QtQuick.Controls
import ScadController

Window {
    x: 10
    y: 10
    width: 340
    height: 280
    visible: true
    title: qsTr("Scad Controller Server")

    Column {
        id: guiColumn
        Button {
            text: "Preview"
            onClicked: {
                ScadControllerServer.preview()
            }
        }
        Button {
            text: "Render"
            onClicked: {
                ScadControllerServer.render()
            }
        }
        Button {
            text: "Show"
            onClicked: {
                ScadControllerServer.show()
            }
        }
        Button {
            text: "Hide"
            onClicked: {
                ScadControllerServer.hide()
            }
        }
        Button {
            text: "Open"
            onClicked: {
                ScadControllerServer.openFile("Dupa dupa dupa test test test 3")
            }
        }
    }

    Rectangle {
        anchors.fill: scadImage
        color: "green"
    }

    ScadImage {
        id: scadImage
        anchors.left: guiColumn.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "image://colors/yellow"
        cache: false

        onWidthChanged: {
            ScadControllerServer.resizeF(width, height)
            //imageSizeChanged(width, height)
            console.log("Width changed to " + width)
        }

        onHeightChanged: {
            ScadControllerServer.resizeF(width, height)
            //imageSizeChanged(width, height)
            console.log("Height changed to " + height)
        }

        Component.onCompleted: {
            ScadControllerServer.resizeF(width, height)
        }

        Connections {
            target: ScadControllerServer
            function onUpdateGLView() {
                console.log("Server recived signal UpdateGLView")
                scadImage.source = ""
                scadImage.source = "image://colors/yellow"
            }
        }
    }
}
