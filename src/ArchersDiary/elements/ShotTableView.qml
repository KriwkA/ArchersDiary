import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import com.archersdiary.models 1.0
import "../dialogs"

Rectangle {
    id: shotTableView;
    property int rowCount;
    property int colCount;
    property int round: 0;

    property int lastSelectedRow;
    property int lastSelectedCol;

    TableView {
        id: table;
        anchors.fill: parent
        alternatingRowColors: false;
        property int colWidth: ( width / ( shotTableView.colCount ) );
        property int rowHeight: ( width / 7.0 ) * 2.0 / 3.0;

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

            ShotTableCell {
                id: cell
                anchors.fill: parent;
                value: styleData.value
            }                                  

            onClicked: {
                if( styleData.column < table.columnCount - 1 ) {
                    var scoreVal = cell.value;
                    lastSelectedRow = styleData.row;
                    lastSelectedCol = styleData.column;
                    shotEditDialog.score = scoreVal.length !== 0 ? (scoreVal !== "M" ? scoreVal : 0) : -1;
                    shotEditDialog.open();
                }
            }            

        }                

        rowDelegate: Rectangle {
            height: table.rowHeight;
        }
    }       

    ShotScoreEditDialog {
        id: shotEditDialog
        x: (window.width - width) / 2.0;
        y: (window.height - height) / 2.0;
        height:  window.height * 2.0 / 3.0;
        onAccepted: {
            shotTableModel.setShotScore( lastSelectedRow, lastSelectedCol, score );
        }
    }
}
