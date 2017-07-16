import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

StackPage {
    ListView {
        id: recordListView
        anchors.fill: parent
        currentIndex: -1

        delegate: ItemDelegate {
            width: recordListView.width
            highlighted: ListView.isCurrentItem

            text: Record ? Record : ""

            onClicked: {
                recordListView.currentIndex = index;
            }
        }

        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            EditButton {
                onClicked: {
                    recordEditDialog.addMode = false;
                    recordEditDialog.open();
                }
                visible: recordListView.currentIndex !== -1
            }

            RemoveButton {
                onClicked: {
                    if( recordModel.removeRow( recordListView.currentIndex ) )
                        recordListView.currentIndex = -1;
                }
                visible: recordListView.currentIndex !== -1
            }

            AddButton {
                onClicked: {
                    recordEditDialog.addMode = true;
                    recordEditDialog.open();
                }
            }

        }

        model: recordModel;
    }

    RecordEditDialog {
        id: recordEditDialog;
        x: (window.width - width) / 2
        y: (window.height - height) / 2
        property bool addMode: true;
        width: window.width;
        height: window.height;
        onAccepted: {
            if(addMode) {
                if( recordModel.addRecord( recordEditDialog.text ) )
                    recordModel.select();
            } else {
                var textRole = recordModel.roleFromRoleName("Record");

                if( textRole !== -1)
                {
                    recordModel.setData(recordListView.currentIndex, recordEditDialog.text, textRole);
                } else {
                    console.log("Error role");
                }
            }
        }
    }

}
