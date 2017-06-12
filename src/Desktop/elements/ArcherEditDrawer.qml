import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1

import "../dialogs"

Drawer {
    ListView {
        id: archerList
        model: archersModel
        onModelChanged: model.select();
        currentIndex: -1
        anchors.fill: parent

        header: ToolBar {

            width: parent.width
            z: 2
            Label {
                Material.foreground: "white"
                text: "Select Archer"
                font.pixelSize: 20
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                anchors.fill: parent
            }
        }

        headerPositioning: ListView.OverlayHeader

        delegate: ItemDelegate {
            width: parent.width
            text: Name ? Name : "";
            highlighted: ListView.isCurrentItem
            onClicked: {
                archerList.currentIndex = index
                editButton.name = Name
                arrowsModel.archerID = Id
            }
            onDoubleClicked: {
                archerListDrawer.close();
            }

        }

        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            ImageButton {
                property string name;
                id: editButton;
                imgSrc: "img/images/edit.png"

                onClicked: {
                    archerEditDialog.currentArcher = archerList.currentIndex;
                    archerEditDialog.name = name;
                    archerEditDialog.open()
                }

                highlighted: true
                visible: archerList.currentIndex !== -1
            }
            ImageButton {
                id: removeButton;
                imgSrc: "img/images/remove.png"
                highlighted: true
                onClicked: {                    
                    if( archersModel.removeRows( archerList.currentIndex, 1) )
                        archerList.currentIndex = -1;

                }
                visible: archerList.currentIndex !== -1
            }
            ImageButton {
                id: addArcherButton
                onClicked: {
                    archerEditDialog.open()
                }
                imgSrc: "img/images/plus.png"
            }
        }

    }

    ArcherEditDialog {
        id: archerEditDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2
    }
}
