import QtQuick
import QtQuick.Controls
import QtWebView
import Flex3D.Editors.BaseEditor

BaseEditor{
    transform: Rotation { origin.x: 25; origin.y: 25; angle: 45}
    WebView {
        anchors.fill: parent
        url: "https://ace.c9.io/build/kitchen-sink.html"
    }
}
