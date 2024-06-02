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
    flags: Qt.WindowStaysOnTopHint

    ScadControllerServer{
        id: scadServer
        onUpdateGLView : {
            console.log("Server recived signal UpdateGLView");
            scadImage.source = "";
            scadImage.source = "image://colors/yellow"
        }
    }

    Column{
        id: guiColumn
        Button{
            text: "Preview"
            onClicked: {
                scadServer.preview()
            }
        }
        Button{
            text:"Render"
            onClicked: {
                scadServer.render()
            }
        }
        Button{
            text:"Show"
            onClicked: {
                scadServer.show()
            }
        }
        Button{
            text:"Hide"
            onClicked: {
                scadServer.hide()
            }
        }
        Button{
            text:"Open"
            onClicked: {
                scadServer.openFile("Dupa dupa dupa test test test 3")
            }
        }
        // RangeSlider {
        //     from: 50
        //     to: 1000
        //     first.value: 240
        //     second.value: 320
        //     first.onMoved: {
        //         scadServer.resizeF(second.value, first.value)
        //     }
        //     second.onMoved: {
        //         scadServer.resizeF(second.value, first.value)
        //     }
        // }
    }


    Rectangle{
        anchors.fill: scadImage
        color: "green"
    }

    Image {
        id: scadImage
        anchors.left: guiColumn.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "image://colors/yellow"
        cache: false

        onWidthChanged: {
            scadServer.resizeF(width, height)
            //imageSizeChanged(width, height)
            console.log("Width changed to " + width)
        }

        onHeightChanged: {
            scadServer.resizeF(width, height)
            //imageSizeChanged(width, height)
            console.log("Height changed to " + height)
        }
        Component.onCompleted: {
            scadServer.resizeF(width, height)
        }

    }
}
