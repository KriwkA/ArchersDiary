import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Dialog {
    property string name: ""
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
            onTextChanged: {
                name = text;
            }
        }

        RowLayout {
            spacing: 20
            Button {
                highlighted: true
                enabled: name.length !== 0
                text: "Ok"
                onClicked: accept()
                Layout.fillWidth: true
            }

            Button {
                highlighted: true
                text: "Cancel"
                onClicked: reject()
                Layout.fillWidth: true
            }
        }
    }  

    onAccepted: {
        if(currentArcher < 0) {
            archersModel.addArcher( archerNameInput.name );
            archersModel.select();
        } else {
            var nameRole = archersModel.roleFromRoleName("Name");
            if(nameRole !== -1)
            {
                arrowsModel.setData(currentArcher, archerNameInput.text, nameRole);
            } else {
                console.log("Error role");
            }
        }
        reset();
    }

    onRejected: {
        reset();
    }

    function reset() {
        name = "";
        currentArcher = -1;
    }
}
