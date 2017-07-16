import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id: shotTableView;
    property int rowCount;
    property int colCount;
    Grid {
        anchors.fill: parent;
        columns: colCount;
        spacing: 2;
        Repeater {
            model: rowCount * colCount;
            Rectangle {
                width: shotTableView.width / colCount;
                height: 25;
                border.width: 1
            }
        }
    }

}
