import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

StackPage {
    id: arrowsPage
    title: "Arrows"
    ListView {
        id: arrowList
        anchors.fill: parent
        currentIndex: -1

        delegate: ItemDelegate {
            id: arrowDelegate
            width: arrowList.width
            highlighted: ListView.isCurrentItem

            text: Name + "\n" +
                  "Spine: " + Spine + "\n" +
                  "Length: " + Length + " mm.\n" +
                  "Diameter: " + Diameter + " mm.";

            onClicked: {
                arrowList.currentIndex = index;                 
                createArrowDialog.name = Name;
                createArrowDialog.spine = Spine;
                createArrowDialog.length = Length;
                createArrowDialog.diameter = Diameter;
            }
        }

        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            EditButton {
                onClicked: {
                    createArrowDialog.editRowInView = arrowList.currentIndex
                    createArrowDialog.open()
                }
                highlighted: true
                visible: arrowList.currentIndex !== -1
            }
            RemoveButton {                
                highlighted: true
                onClicked: {
                    if( arrowsModel.removeRow( arrowList.currentIndex ) )
                        arrowList.currentIndex = -1;
                }
                visible: arrowList.currentIndex !== -1
            }
            AddButton {
                onClicked: {
                    createArrowDialog.open()
                }                
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
