import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 720
    height: 1280
    title: qsTr("Archer's Diary")

    TableView {
        model: ArchersModel

        width: parent.width
        height: parent.height
        headerVisible: true

    }


}
