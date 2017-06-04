import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 720
    height: 1280
    title: qsTr("Archer's Diary")

    header: ToolBar {

    }

    TableView {
        id: tableView

        anchors.fill: parent

        TableViewColumn {
            id: titleColumn
            title: "Id"
            role: "Id"
            movable: false
            resizable: false
            width: tableView.viewport.width * 0.1
            visible: false
        }

        TableViewColumn {
            id: authorColumn
            title: "Name"
            role: "Name"
            movable: false
            resizable: false
            width: tableView.viewport.width - titleColumn.width
        }


        model: ArchersModel
    }


}
