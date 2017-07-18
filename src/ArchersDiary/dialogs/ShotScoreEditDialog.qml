import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

import "../elements"

Dialog {
    id: shotScoreEditDialog
    property int score: -1

    ColumnLayout {
        spacing: 20
        anchors.fill: parent

        ShotScoreSelectList {
            id: shotSelectList;
            shotScore: score
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: 20
            Button {
                highlighted: true
                text: "Ok"
                onClicked: {
                    score = shotSelectList.shotScore;
                    accept();
                }
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
}
