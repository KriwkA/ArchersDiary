import QtQuick 2.7
import QtQuick.Controls 2.2


ToolButton {
    id: button
    property string source;
    contentItem: Image {
        fillMode: Image.Pad
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        source: button.source
    }
}
