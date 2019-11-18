import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../elements"

Dialog {
    focus: true
    modal: true
    property int editRowInView: -1
    property int distance: distanceSpinBox.value;
    property double vertical: verticalSpinBox.realValue;
    property double horisontal: horisontalSpinBox.realValue;
    padding: 0

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        SpinBox {
            id: distanceSpinBox
            from: 1
            to: 200
            value: distance
            stepSize: 1
            editable: true
        }

        DoubleSpinBox {
            id: verticalSpinBox
            decimals: 1
            realFrom: 0.0
            realTo: 20.0
            realValue: vertical
            realStepSize: 0.1
            editable: true
        }

        DoubleSpinBox {
            id: horisontalSpinBox
            decimals: 1
            realFrom: 0.0
            realTo: 5.0
            realValue: horisontal
            realStepSize: 0.1
            editable: true
        }

        RowLayout {
            spacing: 20
            Button {
                highlighted: true
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
            title = "Add Scope";
            distanceSpinBox.value = 18;
            verticalSpinBox.realValue = ( verticalSpinBox.realFrom + verticalSpinBox.realTo ) * 0.5;
            horisontalSpinBox.realValue = ( horisontalSpinBox.realFrom + horisontalSpinBox.realTo ) * 0.5;
        } else {
            title = "Edit Scope";
            distanceSpinBox.value = distance;
            verticalSpinBox.realValue = vertical;
            horisontalSpinBox.realValue = horisontal;
        }
    }

    onAccepted: {
        if(editRowInView < 0) {
            scopesModel.addScope( distanceSpinBox.value, verticalSpinBox.realValue, horisontalSpinBox.realValue );
            scopesModel.select();
        } else {
            var distanceRole = scopesModel.roleFromRoleName("Distance");
            var verticalRole = scopesModel.roleFromRoleName("Vertical");
            var horisontalRole = scopesModel.roleFromRoleName("Horizontal");

            if( !( distanceRole === -1 || verticalRole === -1 || horisontalRole === -1 ) )
            {
                scopesModel.setData(editRowInView, distanceSpinBox.value, distanceRole);
                scopesModel.setData(editRowInView, verticalSpinBox.realValue, verticalRole);
                scopesModel.setData(editRowInView, horisontalSpinBox.realValue, horisontalRole);
            } else {
                console.log("Error role");
            }
        }
    }
}
