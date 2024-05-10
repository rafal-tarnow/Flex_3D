import QtQuick
import QtQuick.Controls
import QtWebView
import QtWebEngine
import Flex3D.Editors.BaseEditor

BaseEditor {
    id: root
    WebEngineView {
        id: webContent
        anchors.fill: parent
        url: "qrc:/ide.html"
        property bool pageLoaded: false

        function setEditorText(text) {
            if (pageLoaded) {
                runJavaScript('setText(' + JSON.stringify(text) + ');')
            }
        }

        onLoadingChanged: function (loadingInfo) {
            //Calling the script loading the text must occur after the page is loaded, calling the script earlier causes a reference error to the Ace editor.
            if (loadingInfo.status === WebEngineView.LoadSucceededStatus) {
                webContent.pageLoaded = true
                webContent.setEditorText(root.text)
            }
        }

        function requestText(callback) {
            if (pageLoaded)
                runJavaScript('editor.getValue();', callback)
            else
                console.warn("WARNING: Try request text before page loaded!")
        }

        function format() {
            runJavaScript('format();')
        }
    }

    onTextChanged: {
        webContent.setEditorText(root.text)
    }

    function requestText(callback) {
        return webContent.requestText(callback)
    }
    function format() {
        webContent.format()
    }
}
