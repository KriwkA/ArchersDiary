import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

Page {
    id: arrowsPage
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
                editButton.name = Name;
                editButton.spine = Spine;
                editButton.length = Length;
                editButton.diameter = Diameter;
            }
        }


        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            ImageButton {
                property string name;
                property double spine;
                property double length;
                property double diameter;

                id: editButton;
                imgSrc: "img/images/edit.png"

                onClicked: {
                    createArrowDialog.editRowInView = arrowList.currentIndex;
                    createArrowDialog.name = name;
                    createArrowDialog.spine = spine;
                    createArrowDialog.length = length;
                    createArrowDialog.diameter = diameter;
                    createArrowDialog.open()
                }
                highlighted: true
                visible: arrowList.currentIndex !== -1
            }
            ImageButton {
                id: removeButton;
                imgSrc: "img/images/remove.png"
                highlighted: true
                onClicked: {
                    if( arrowsModel.removeRows(arrowList.currentIndex, 1) )
                        arrowList.currentIndex = -1;
                }
                visible: arrowList.currentIndex !== -1
            }
            ImageButton {
                id: addArrowButton
                onClicked: {
                    createArrowDialog.open()
                }
                imgSrc: "img/images/plus.png"
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
