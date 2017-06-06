import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import "../elements"

Page {
    id: arrowsPage
    ListView {
        id: arrowList
        anchors.fill: parent
        currentIndex: -1

        delegate: ItemDelegate {
            width: arrowList.width
            text: Name + "\n" +
                  "Spine: " + Spine + "\n" +
                  "Length: " + Length + " mm.\n" +
                  "Diametr: " + Diameter + " mm.";
            onClicked: {
                arrowList.currentIndex = index
            }
        }

        AddButton {
            parent: arrowList
            x : parent.width - width - 20
            y : parent.height - height - 20
            onClicked: {
                createArrowDialog.open()
            }
        }

        model: arrowsModel
    }

    Dialog {
        id: createArrowDialog

//        x: (window.width - width) / 2
//        y: (window.height - height) / 2

        focus: true
        modal: true
        title: "Create Arrow"

        ColumnLayout {
            spacing: 20
            anchors.fill: parent

            TextField {
                id: arrowName
                focus: true
                placeholderText: "Arrow name"
                Layout.fillWidth: true
            }

            SpinBox {
                id: spine
                from: 200
                to: 1200
                value: 600
                stepSize: 10
            }

            DoubleSpinBox {
                id: length
                realFrom: 500.0
                realTo: 800.0
                realValue: 650.0
                realStepSize: 5.0
            }

            DoubleSpinBox {
                id: diameter
                realFrom: 3.0
                realTo: 15.0
                realValue: 5.5
                realStepSize: 0.1
            }

            RowLayout {
                Button {
                  enabled: arrowName.length !== 0
                  text: "Ok"
                  onClicked: createArrowDialog.accept()
                }

                Button {
                  text: "Cancel"
                  onClicked: createArrowDialog.reject()
                }
            }
        }

        onAccepted: {
            arrowsModel.addArrow(arrowName.text, spine.value, length.realValue, diameter.realValue)
            arrowsModel.select();
            arrowName.text = "";
        }
    }

}
