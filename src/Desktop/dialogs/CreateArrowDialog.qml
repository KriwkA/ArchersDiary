import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../elements"

Dialog {
    focus: true
    modal: true
    property int editRowInView: -1
    property ListView view;
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
        }

        DoubleSpinBox {
            id: lengthSpinBox
            realFrom: 500.0
            realTo: 800.0
            realValue: length
            realStepSize: 5.0
            editable: true
        }

        DoubleSpinBox {
            id: diameterSpinBox
            realFrom: 3.0
            realTo: 15.0
            realValue: diameter
            realStepSize: 0.1
            editable: true           
        }

        RowLayout {
            spacing: 20
            Button {
                highlighted: true
                enabled: arrowName.length !== 0
                text: "Ok"
                onClicked: createArrowDialog.accept()
                Layout.fillWidth: true
            }

            Button {
                highlighted: true
                text: "Cancel"
                onClicked: createArrowDialog.reject()
                Layout.fillWidth: true
            }
        }
    }

    onOpened: {
        if(editRowInView < 0) {
            title = "Create Arrow";
            arrowName.text = "";
            spineSpinBox.value = (spineSpinBox.from + spineSpinBox.to) / 2
            lengthSpinBox.real = (lengthSpinBox.from + lengthSpinBox.to) / 2
            diameterSpinBox.value = (diameterSpinBox.from + diameterSpinBox.to) / 2
        } else {
            title = "Edit Arrow";            
        }
    }

    onClosed: {
        editRowInView = -1;
    }

    onAccepted: {
        if(editRowInView < 0) {
            view.model.addArrow(arrowName.text, spineSpinBox.value, lengthSpinBox.realValue, diameterSpinBox.realValue)
            view.model.select();
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
                console.log(diameterSpinBox.realValue);
                arrowsModel.setData(editRowInView, diameterSpinBox.realValue, diameterRole);
                arrowsModel.acc
            } else {
                console.log("Error role");
            }
        }
    }

}
