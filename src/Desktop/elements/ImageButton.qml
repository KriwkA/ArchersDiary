import QtQuick 2.6
import QtQuick.Controls 2.1

RoundButton {
    property string imgSrc;
    highlighted: true    

    contentItem: Image {
        fillMode: Image.Pad
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        width: 50
        height: 50
        source: "../" + imgSrc;
    }
}
