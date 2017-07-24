import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    property string value;
    color: "black"
    anchors.fill: parent;
    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.rightMargin: 1;
        anchors.bottomMargin: 1;
        Label {
            anchors.fill: parent
            text: value;
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }
    }
}
