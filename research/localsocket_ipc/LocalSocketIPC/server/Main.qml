import QtQuick
import QtQuick.Controls
import LocalSocketIPCServer

Window {
    x: 10
    y: 10
    width: 340
    height: 280
    visible: true
    title: qsTr("Localhost Server")
    flags: Qt.WindowStaysOnTopHint

    ScadControllerServer{
        id: scadServer
        onUpdateGLView : {
            console.log("Server recived signal UpdateGLView");
        }
    }

    Column{
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
            text:"Open"
            onClicked: {
                scadServer.openFile("Dupa dupa dupa test test test 3")
            }
        }
    }
}
