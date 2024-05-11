import QtQuick
import QtQuick.Controls
import QtWebView
import QtWebEngine
import Flex3D.Editors.BaseEditor

BaseEditor {
    id: root
    signal editorReady
    WebEngineView {
        id: webContent
        anchors.fill: parent
        url: "qrc:/ide.html"

        function setEditorText(text) {
            runJavaScript('setText(' + JSON.stringify(text) + ');')
        }

        onLoadingChanged: function (loadingInfo) {
            //Calling the script loading the text must occur after the page is loaded, calling the script earlier causes a reference error to the Ace editor.
            if (loadingInfo.status === WebEngineView.LoadSucceededStatus) {
                root.editorReady()
            }
        }

        function requestText(callback) {
            runJavaScript('editor.getValue();', callback)
        }

        function format() {
            runJavaScript('format();')
        }
    }

    function setText(text) {
        webContent.setEditorText(text)
    }

    function requestText(callback) {
        return webContent.requestText(callback)
    }
    function format() {
        webContent.format()
    }
}
