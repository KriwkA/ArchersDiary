import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import "../elements"
import "../dialogs"

Page {
    id: arrowsPage
    ListView {
        id: arrowList
        anchors.fill: parent
        currentIndex: -1

        delegate: ItemDelegate {
            width: arrowList.width
            text: Name + "\n" +
                  "Spine: " + Spine + "\n" +
                  "Length: " + Length + " mm.\n" +
                  "Diametr: " + Diameter + " mm.";
            onClicked: {
                arrowList.currentIndex = index
            }
        }

        AddButton {
            parent: arrowList
            x : parent.width - width - 20
            y : parent.height - height - 20
            onClicked: {
                createArrowDialog.open()
            }
        }

        model: arrowsModel
    }

    CreateArrowDialog {
        id: createArrowDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2
    }


}
