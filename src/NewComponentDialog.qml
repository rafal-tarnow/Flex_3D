import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: dialog
    title: qsTr("New Component")

    width: 400

    signal finished(string componentName)

    focus: true
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: GridLayout {
        id: grid
        property alias componentName: componentName
        property int minimumInputSize: 120
        property string placeholderText: qsTr("<enter>")

        rows: 5
        columns: 2

        Label {
            text: qsTr("Component Name")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }

        TextField {
            id: componentName
            focus: true
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
            placeholderText: grid.placeholderText
            onTextChanged: validateComponentName(
                               ) // Wywołanie funkcji walidacji przy każdej zmianie tekstu
        }

        Label {
            id: rulesLabel
            Layout.columnSpan: 2
            text: qsTr("* Name must start with a capital letter\n* Only letters and digits are allowed\n* Use CamelCase for multi-word names")
            wrapMode: Text.WordWrap
            color: "gray"
            Layout.alignment: Qt.AlignLeft
        }

        Label {
            id: validationLabel
            Layout.columnSpan: 2
            text: ""
            color: "black"
            Layout.alignment: Qt.AlignCenter
        }
    }

    function validateComponentName() {
        var pattern = /^[A-Z][a-zA-Z0-9]*$/
        if (pattern.test(componentName.text)) {
            validationLabel.text = qsTr("Name valid")
            validationLabel.color = "green"
        } else {
            validationLabel.text = qsTr("Name not valid")
            validationLabel.color = "red"
        }
    }

    onOpened: componentName.text = ""

    onAccepted: {
        if (componentName.text) {
            if (validationLabel.text === qsTr("Name valid")) {
                finished(componentName.text)
            } else {
                // Optionally, you can prevent closing if the name is not valid
                dialog.open()
            }
        }
    }
}
