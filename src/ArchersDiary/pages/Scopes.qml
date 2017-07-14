import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

Page {

    id: scopePage
    ListView {
        id: scopeList
        anchors.fill: parent
        currentIndex: -1

        delegate: ItemDelegate {
            id: scopeDelegate
            width: scopeList.width
            highlighted: ListView.isCurrentItem

            text: "Distance: " + Distance + " m\n" +
                  "Vertical: " + Vertical + "\n"+
                  "Horizontal: " + Horizontal + " cm";

            onClicked: {
                scopeList.currentIndex = index;
            }
        }


        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            AddButton {
                id: addScope
                onClicked: {
                    scopeEditDialog.open();
                }
            }

        }

        model: scopesModel
    }

    ScopeEditDialog {
        id: scopeEditDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2
    }
}
