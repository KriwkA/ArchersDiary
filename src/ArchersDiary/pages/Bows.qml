import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"

Page {

    id: bowsPage
    ListView {
        id: bowList
        anchors.fill: parent
        currentIndex: -1

        delegate: ItemDelegate {
            id: bowDelegate
            width: bowList.width
            highlighted: ListView.isCurrentItem

            text: "None"

            onClicked: {
                bowList.currentIndex = index;
            }
        }


        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            ImageButton {
                id: addBow
                onClicked: {

                }
                imgSrc: "img/images/plus.png"
            }
        }

        model: bowsModel
    }
}
