import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

Page {

    id: scopePage
    title: "Scopes"
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
                scopeEditDialog.distance = Distance;
                scopeEditDialog.vertical = Vertical;
                scopeEditDialog.horisontal = Horizontal;
            }

        }


        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            property bool isItemSelected: scopeList.currentIndex >= 0

            EditButton {
                id: scopeEditButton
                visible: parent.isItemSelected
                onClicked: {
                    scopeEditDialog.editRowInView = scopeList.currentIndex;
                    scopeEditDialog.open();
                }
            }

            RemoveButton {
                visible: parent.isItemSelected
                onClicked: {
                    var oldIndex = scopeList.currentIndex;
                    if( scopesModel.removeRow( oldIndex ) ) {
                        scopeList.currentIndex = oldIndex - 1;
                    }
                }
            }

            AddButton {                
                onClicked: {
                    scopeEditDialog.editRowInView = -1;
                    scopeEditDialog.open();
                }
            }

        }

        model: scopesModel

        onCurrentIndexChanged: {
            scopeEditDialog.editRowInView = currentIndex;
        }

    }

    ScopeEditDialog {
        id: scopeEditDialog
        x: (window.width - width) / 2
        y: (window.height - height) / 2
    }


}
