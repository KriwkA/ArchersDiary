import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../elements"

Dialog {
    focus: true
    modal: true
    property int editRowInView: -1    
    property string name: arrowName.text;
    property double spine: spineSpinBox.value;
    property double length: lengthSpinBox.realValue;
    property double diameter: diameterSpinBox.realValue;

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        TextField {
            id: arrowName
            focus: true
            placeholderText: "Arrow name"
            Layout.fillWidth: true
            text: name
            KeyNavigation.tab: spineSpinBox
        }

        Label {
            text : "Spine"
            height: spineSpinBox.height * 2 / 3
        }

        SpinBox {
            id: spineSpinBox
            from: 200
            to: 1200
            value: spine
            stepSize: 10
            editable: true
            KeyNavigation.tab: lengthSpinBox
        }

        DoubleSpinBox {
            id: lengthSpinBox
            realFrom: 500.0
            realTo: 800.0
            realValue: length
            realStepSize: 5.0
            editable: true
            KeyNavigation.tab: diameterSpinBox
        }

        DoubleSpinBox {
            id: diameterSpinBox
            realFrom: 3.0
            realTo: 15.0
            realValue: diameter
            realStepSize: 0.1
            editable: true
            KeyNavigation.tab: acceptButton
        }

        RowLayout {
            spacing: 20
            Button {
                id: acceptButton
                highlighted: true
                enabled: arrowName.length !== 0
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
        if( editRowInView < 0 ) {
            title = "Create Arrow";
            arrowName.text = "";
            spineSpinBox.value = (spineSpinBox.from + spineSpinBox.to) / 2
            lengthSpinBox.value = (lengthSpinBox.from + lengthSpinBox.to) / 2
            diameterSpinBox.value = (diameterSpinBox.from + diameterSpinBox.to) / 2
        } else {
            title = "Edit Arrow";
            spineSpinBox.value = spine
            lengthSpinBox.realValue = length
            diameterSpinBox.realValue = diameter
        }        
    }

    onClosed: {
        editRowInView = -1;
    }

    onAccepted: {
        if(editRowInView < 0) {
            arrowsModel.addArrow(arrowName.text, spineSpinBox.value, lengthSpinBox.realValue, diameterSpinBox.realValue)
            arrowsModel.select();
        } else {
            var nameRole = arrowsModel.roleFromRoleName("Name");
            var spineRole = arrowsModel.roleFromRoleName("Spine");
            var lengthRole = arrowsModel.roleFromRoleName("Length");
            var diameterRole = arrowsModel.roleFromRoleName("Diameter");
            if(!(nameRole === -1 || spineRole === -1 || lengthRole === -1 || diameterRole === -1 ))
            {
                arrowsModel.setData(editRowInView, arrowName.text, nameRole);
                arrowsModel.setData(editRowInView, spineSpinBox.value, spineRole);
                arrowsModel.setData(editRowInView, lengthSpinBox.realValue, lengthRole);
                arrowsModel.setData(editRowInView, diameterSpinBox.realValue, diameterRole);
            } else {
                console.log("Error role");
            }
        }
    }

}
