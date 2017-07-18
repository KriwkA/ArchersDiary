import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import com.archersdiary.models 1.0
import "../dialogs"

Rectangle {
    id: shotTableView;
    property int rowCount: 6;
    property int colCount: 6;
    property int round: 0;
    TableView {
        id: table;
        anchors.fill: parent
        property int colWidth: ( width / ( shotTableView.colCount + 1 ) );
        TableViewColumn { role: "FirstArrow";   title: "1";     visible: colCount > 0; width: table.colWidth  }
        TableViewColumn { role: "SecondArrow";  title: "2";     visible: colCount > 1; width: table.colWidth  }
        TableViewColumn { role: "ThirdArrow";   title: "3";     visible: colCount > 2; width: table.colWidth  }
        TableViewColumn { role: "FourthArrow";  title: "4";     visible: colCount > 3; width: table.colWidth  }
        TableViewColumn { role: "FifthArrow";   title: "5";     visible: colCount > 4; width: table.colWidth  }
        TableViewColumn { role: "SixthArrow";   title: "6";     visible: colCount > 5; width: table.colWidth  }
        TableViewColumn { role: "SeriesScore";  title: "Total"; visible: colCount > 0; width: table.colWidth  }

        model: ShotTableModel {
            id: shotTableModel;
            round: shotTableView.round;
        }

        itemDelegate: MouseArea {
            id: mouseArea
            Text {
                id: scoreVal
                text: shotTableModel.shotScore( styleData.row, styleData.column );
            }

            ShotScoreEditDialog {
                id: shotEditDialog
                score: scoreVal.text.length !== 0 ? (scoreVal.text !== "M" ? scoreVal.text : 0) : -1;
                y: parent.bottom
            }

            onClicked: {
                console.log( styleData.row + ' ' + styleData.column );
                shotEditDialog.open();
            }
        }
    }

}
