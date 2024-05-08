import QtQuick
import QtQuick.Controls
import QtWebView
import QtWebEngine
import Flex3D.Editors.BaseEditor

BaseEditor{
    WebView {
        anchors.fill: parent
        url: "qrc:/ide.html"
    }
}
