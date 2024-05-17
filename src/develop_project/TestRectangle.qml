import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    Button {
        text: "Test backend"
        onClicked: {
            console.log(root.parent.testTxt)
            //backend.testBackendCall()
        }
    }
    width: 300
    height: 300
    color: "red"
}
