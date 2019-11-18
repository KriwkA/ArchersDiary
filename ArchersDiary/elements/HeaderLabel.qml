import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

Label {
    Material.foreground: "white"
    id: titleLabel
    font.pixelSize: 20
    elide: Label.ElideRight
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    Layout.fillWidth: true
}
