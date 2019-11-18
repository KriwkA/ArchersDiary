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
        property bool recordSelected: currentIndex !== -1

        function setArcherToModels( id ) {
            trainingModel.archerID = id;
        }

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
                archerList.setArcherToModels( Id );
            }
            onDoubleClicked: {
                archerListDrawer.close();
            }

        }

        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            EditButton {
                property string name;
                id: editButton
                visible: archerList.recordSelected;
                onClicked: {
                    archerEditDialog.currentArcher = archerList.currentIndex;
                    archerEditDialog.name = name;
                    archerEditDialog.open()
                }


            }
            RemoveButton {
                visible: archerList.recordSelected;
                onClicked: {                    
                    if( archersModel.removeRow( archerList.currentIndex ) ) {
                        archerList.currentIndex = -1;
                        archerList.setArcherToModels( -1 );
                    }
                }
            }
            AddButton {
                onClicked: archerEditDialog.open();
            }
        }

    }

    ArcherEditDialog {
        id: archerEditDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2
    }
}
