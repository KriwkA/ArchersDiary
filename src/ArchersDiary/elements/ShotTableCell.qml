import QtQuick 2.0

Rectangle {
    property string value;
    color: "black"
    anchors.fill: parent;
    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.rightMargin: 1;
        anchors.bottomMargin: 1;
        Text {           
            anchors.fill: parent
            text: value;
            horizontalAlignment: Qt.AlignCenter
            verticalAlignment: Qt.AlignCenter
            onTextChanged: {
                console.log( "Text: " + text );
            }
        }
    }
    onValueChanged: {
        console.log( "Value: " + value);
    }
}
