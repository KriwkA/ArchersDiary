import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: mainRec;
    property int score;
    property bool total: false;
    color: "Black"
    anchors.fill: parent;
    Rectangle {

        color: {
            if( !total ) {
                switch ( score ) {
                    case 5:  "blue"; break;
                    case 6:  "blue"; break;
                    case 7:  "red"; break;
                    case 8:  "red"; break;
                    case 9:  "yellow"; break;
                    case 10: "yellow"; break;
                    default: "white";
                }
            } else {
                "white";
            }
        }

        anchors.fill: parent        
        anchors.bottomMargin: 1;
        anchors.rightMargin: 1;
        Label {
            anchors.fill: parent
            text: score === 0 ? (total ? 0 : "M") : ( score === -1 ? "" : score );
            color: "Black"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }
    }
}
