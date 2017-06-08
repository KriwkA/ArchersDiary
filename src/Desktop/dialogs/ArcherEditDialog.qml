import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Dialog {
    property string name: archerNameInput.text
    property int currentArcher: -1

    focus: true
    modal: true
    title: "Add Archer"    

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        TextField {
            id: archerNameInput
            focus: true
            placeholderText: "Enter your name"
            Layout.fillWidth: true
            text: name
        }

        RowLayout {
            Button {
              enabled: name.length !== 0
              text: "Ok"
              onClicked: accept()
            }

            Button {
              text: "Cancel"
              onClicked: reject()
            }
        }
    }    
}
