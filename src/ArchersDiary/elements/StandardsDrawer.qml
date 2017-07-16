import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


Drawer {    

    ListView {
        id: standardList
        model: standardModel
        onModelChanged: model.select();
        currentIndex: -1
        anchors.fill: parent        

        header: ToolBar {

            width: parent.width
            z: 2
            Label {
                Material.foreground: "white"
                text: "Select Standard"
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
            onClicked: {
                trainingStandardModel.addStandard( Id );
                close();
            }
        }
    }
    onOpened: {
        standardModel.select();
    }
}
