import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../elements"

Dialog {
    id: shotScoreEditDialog
    property int score: -1

    padding: 0
    margins: 1

    function clickSelect( value ) {
        if( value === -1 ) {
            score = -1;
            reject();
            return;
        }

        score = value;
        accept();
    }

    ColumnLayout {
        anchors.fill: parent;
        spacing: 1

        RowLayout {
            spacing: 1
            ScoreButton { score: 10; onClicked: shotScoreEditDialog.clickSelect( 10 ); }
            ScoreButton { score: 9; onClicked: shotScoreEditDialog.clickSelect( 9 ); }
            ScoreButton { score: 8; onClicked: shotScoreEditDialog.clickSelect( 8 ); }
        }
        RowLayout {
            spacing: 1
            ScoreButton { score: 7; onClicked: shotScoreEditDialog.clickSelect( 7 ); }
            ScoreButton { score: 6; onClicked: shotScoreEditDialog.clickSelect( 6 ); }
            ScoreButton { score: 5; onClicked: shotScoreEditDialog.clickSelect( 5 ); }
        }
        RowLayout {
            spacing: 1
            ScoreButton { score: 4; onClicked: shotScoreEditDialog.clickSelect( 4 ); }
            ScoreButton { score: 3; onClicked: shotScoreEditDialog.clickSelect( 3 ); }
            ScoreButton { score: 2; onClicked: shotScoreEditDialog.clickSelect( 2 ); }
        }
        RowLayout {
            spacing: 1
            ScoreButton { score: 1; onClicked: shotScoreEditDialog.clickSelect( 1 ); }
            ScoreButton { score: 0; onClicked: shotScoreEditDialog.clickSelect( 0 ); }
            ScoreButton { score: -1; onClicked: shotScoreEditDialog.clickSelect( -1 ); }
        }
    }
}
