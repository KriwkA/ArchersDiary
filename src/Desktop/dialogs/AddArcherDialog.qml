import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Dialog {
    focus: true
    modal: true
    title: "Add Archer"
    standardButtons: archerNameInput.text.length !== 0 ? Dialog.Ok | Dialog.Cancel : Dialog.Cancel

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        TextField {
            id: archerNameInput
            focus: true
            placeholderText: "Enter your name"
            Layout.fillWidth: true
        }
    }

    onAccepted: {
        archersModel.addArcher(archerNameInput.text);
        archersModel.select();
        archerNameInput.text = "";
    }
}
