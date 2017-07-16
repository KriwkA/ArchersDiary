import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"


StackPage {
    padding: 20

    ColumnLayout {

        spacing: 20
        anchors.fill: parent

        Label {
            width: parent.width
            text: "Standards:"
            horizontalAlignment: Qt.AlignCenter
        }

        Frame {
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView {
                id: standardList
                anchors.fill: parent


                delegate: ItemDelegate {
                    width: standardList.width
                    highlighted: ListView.isCurrentItem

                    text: standardModel.standardName( Standard );

                    onClicked: {
                        standardList.currentIndex = index;
                        excerciseModel.select();
                        standardExcerciseModel.standardID = Standard;
                        standardExcerciseModel.select();
                        stackView.title = "Standard";
                        stackView.push( "StandardPage.qml" );
                    }
                }

                AddButton {
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    onClicked: {
                        standardsDrawer.open();
                    }
                }

                StandardsDrawer {
                    id: standardsDrawer
                    dragMargin: 0
                    width: Math.min(parent.width, window.height) / 3 * 2
                    height: parent.height
                }

                model: trainingStandardModel
            }
        }

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
                horizontalAlignment: Qt.AlignRight
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
    }
}
