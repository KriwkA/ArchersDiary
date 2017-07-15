import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import "../elements"
import "../pages"

StackPage {
    id: trainingDialog;
    padding: 20

    ColumnLayout {

        spacing: 20
        anchors.fill: parent

        Button {
            height: 50;
            Layout.fillWidth: true
            text: "Show records"
            onClicked: {
                stackView.title = "Records";
                stackView.push( "RecordPage.qml" );
                recordModel.select();
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                width: parent.width
                text: "Shot count:"
                horizontalAlignment: "AlignRight"
            }

            SpinBox {
                Layout.fillWidth: true
                value: trainingModel.shotCount;
                from: 0;
                to: 5000;
                stepSize: 1;
                onValueChanged: trainingModel.shotCount = value;
            }
        }

        //spacer
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
