import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

StackPage {
    id: bowsPage
    title: "Bows"
    ListView {
        id: bowList
        anchors.fill: parent
        currentIndex: -1

        function setBowIdToModels( id ) {
            scopesModel.bowID = id;
        }

        delegate: ItemDelegate {
            id: bowDelegate
            width: bowList.width
            highlighted: ListView.isCurrentItem

            text: Name + "\n" +
                  "Handle: " + Handle + "\n" +
                  "Limbs: " + Limbs;

            onClicked: {
                bowList.currentIndex = index;
                bowList.setBowIdToModels( Id );
            }
        }


        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            ImageButton {
                id: addBow
                onClicked: {
                    createBowDialog.open();
                }
                imgSrc: "img/images/plus.png"
            }
        }

        model: bowsModel
    }

    BowEditDialog {
        id: createBowDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2
    }
}
