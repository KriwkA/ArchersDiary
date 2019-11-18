import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Dialog {
    focus: true
    modal: true
    id: recordEditDialog

    property string text: textInput.text;

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        TextField {
            id: textInput
            text: recordEditDialog.text;
            maximumLength: 255;
        }

        RowLayout {
            spacing: 20
            Button {
                highlighted: true
                text: "Ok"
                onClicked: accept()
                Layout.fillWidth: true
                enabled: textInput.text.length !== 0
            }

            Button {
                highlighted: true
                text: "Cancel"
                onClicked: reject()
                Layout.fillWidth: true
            }
        }
    }
}
