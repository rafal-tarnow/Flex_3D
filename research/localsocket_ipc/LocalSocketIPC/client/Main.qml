import QtQuick
import QtQuick.Controls
import LocalSocketIPCClient

Window {
    x:400
    y:10
    width: 340
    height: 280
    visible: true
    title: qsTr("Localhost Client")
    flags: Qt.WindowStaysOnTopHint

    ScadControllerClient{
        id: scadClient

        onPreview: {
            console.log("Preview signal received in client.")
        }

        onRender: {
            console.log("Render signal received in client.")
        }

        onOpenFile: function(filePath) {
            console.log("OpenFile signal received in client with file path:" + filePath)
        }
    }

    Column{
        Button{
            text: "update GL View"
            onClicked: {
                scadClient.updateGLView()
            }
        }
    }

}
