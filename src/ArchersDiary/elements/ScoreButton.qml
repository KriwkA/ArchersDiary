import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Button {
    property int score;
    Layout.fillHeight: true;
    Layout.fillWidth: true;

    style: ButtonStyle {
        background: Rectangle {
            color: {
                switch ( score )
                {
                case 3: "black"; break;
                case 4: "black"; break;
                case 5:  "blue"; break;
                case 6:  "blue"; break;
                case 7:  "red"; break;
                case 8:  "red"; break;
                case 9:  "yellow"; break;
                case 10: "yellow"; break;
                default: "white";
                }
            }
        }
        label: Label {
            Label {
                anchors.fill: parent;
                id: button
                text: score === 0 ? "M" : ( score === -1 ? "X" : score );

                color: !(score === 3 || score === 4) ? "Black" : "White";
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                font.pointSize: 26;
            }
        }
    }
}
