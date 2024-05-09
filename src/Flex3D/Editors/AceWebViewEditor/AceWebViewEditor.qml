import QtQuick
import QtQuick.Controls
import QtWebView
import QtWebEngine
import Flex3D.Editors.BaseEditor

BaseEditor{
    id:root
    WebEngineView {
        id: webContent
        anchors.fill: parent
        url: "qrc:/ide.html"
        property bool firstTimeTextLoaded: false

        function setEditorText(text) {
            if(firstTimeTextLoaded){
                runJavaScript('editor.setValue(' + JSON.stringify(text) + ');');
            }
        }

        onLoadingChanged:function(loadingInfo){
            //Calling the script loading the text must occur after the page is loaded, calling the script earlier causes a reference error to the Ace editor.
            if(loadingInfo.status === WebEngineView.LoadSucceededStatus){
                webContent.firstTimeTextLoaded = true;
                webContent.setEditorText(root.text);
            }
        }
    }

    onTextChanged: {
        webContent.setEditorText(root.text);
    }
}
