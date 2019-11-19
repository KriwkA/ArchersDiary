import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../elements"
import "../dialogs"

StackPage {
    id: standardPage
    property int trainingStandardID;
    property int roundNumber: 0;
    property int roundCount: standardExcerciseModel.excerciseCount();        

    function excerciseId() {
        return standardExcerciseModel.excerciseId( roundNumber );
    }

    function excerciseName() {
        return excerciseModel.excerciseName( excerciseId() );
    }

    function shotsPerSerie() {
        return excerciseModel.shotPerSerie( excerciseId() );
    }

    function seriesCount() {
        return excerciseModel.seriesCount( excerciseId() );
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10;

        ShotTableView {
            id: shotTableView;
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            rowCount: seriesCount();
            colCount: shotsPerSerie();
            round: roundNumber;
        }


        Label {
            id: totalScoreText;
            Layout.fillWidth: true;
            height: 32
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text: "Total: " + shotTableView.totalScore;
        }

        RowLayout {
            Layout.fillWidth: true

            id: bottomLayout

            ImageButton {               
                enabled: roundNumber > 0;
                imgSrc: BackImage;
                onClicked: {
                    roundNumber--;
                }                
            }

            Label {
                Layout.fillWidth: true;
                height: 32;
                text: excerciseName();
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
            }

            ImageButton {
                enabled: roundNumber < roundCount - 1;
                imgSrc: ForwardImage;
                onClicked: {
                    roundNumber++;
                }
            }

        }

    }

}
