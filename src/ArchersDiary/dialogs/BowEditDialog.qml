import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../elements"

Dialog {
    focus: true
    modal: true
    property int editRowInView: -1
    property string name: bowName.text;
    property string handle: bowHandle.text;
    property string limbs: bowLimbs.text;

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        TextField {
            id: bowName
            focus: true
            placeholderText: "Name:"
            Layout.fillWidth: true
            text: name
        }

        TextField {
            id: bowHandle
            focus: true
            placeholderText: "Handle:"
            Layout.fillWidth: true
            text: handle
        }

        TextField {
            id: bowLimbs
            focus: true
            placeholderText: "Limbs:"
            Layout.fillWidth: true
            text: limbs
        }

        RowLayout {
            spacing: 20
            Button {
                id: acceptButton
                highlighted: true
                enabled: bowName.length !== 0 && bowHandle.length !== 0 && bowLimbs.length !== 0
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

    onOpened: {
        if(editRowInView < 0) {
            title = "Create Bow";
            bowName.text = "";
            bowHandle.text = "";
            bowLimbs.text = "";
        } else {
            title = "Edit Bow";
            bowName.text = name;
            bowHandle.text = handle;
            bowLimbs.text = limbs;
        }
    }

    onClosed: {
        editRowInView = -1;
    }

    onAccepted: {
        if(editRowInView < 0) {
            bowsModel.addBow( bowName.text, bowHandle.text, bowLimbs.text );
            bowsModel.select();
        } else {
            var nameRole = bowsModel.roleFromRoleName("Name");
            var handleRole = bowsModel.roleFromRoleName("Handle");
            var limbsRole = bowsModel.roleFromRoleName("Limbs");
            if(!(nameRole === -1 || handleRole === -1 || limbsRole === -1 ))
            {
                arrowsModel.setData(editRowInView, bowName.text, nameRole);
                arrowsModel.setData(editRowInView, bowHandle.value, handleRole);
                arrowsModel.setData(editRowInView, bowLimbs.realValue, limbsRole);
            } else {
                console.log("Error role");
            }
        }
    }
}

