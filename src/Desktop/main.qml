import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1


ApplicationWindow {    
    visible: true
    width: 720 / 2
    height: 1280 / 2
    title: qsTr("Archer's Diary")

    header: ToolBar {

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "images/drawer.png";
                }
                onClicked: {

                }
            }

            Label {
                id: titleLabel
                text: "Archers"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "images/menu.png"
                }
                onClicked: addArcherDialog.open()

                Dialog {
                    id: addArcherDialog
                    parent: tableView

                    x: (parent.width - width) / 2
                    y: (parent.height - height) / 2

                    focus: true
                    modal: true
                    title: "Add Archer"
                    standardButtons: archerNameInput.text.length !== 0 ? Dialog.Ok | Dialog.Cancel : Dialog.Cancel


                    ColumnLayout {
                        spacing: 20
                        anchors.fill: parent

                        TextField {
                            id: archerNameInput
                            focus: true
                            placeholderText: "Enter your name"
                            Layout.fillWidth: true

                        }
                    }

                    onAccepted: {
                        ArchersModel.addArcher(archerNameInput.text);
                        ArchersModel.select();
                    }
                }
            }
        }
    }

    TableView {
        id: tableView

        anchors.fill: parent
        headerVisible: false

        TableViewColumn {
            id: titleColumn
            title: "Id"
            role: "Id"
            movable: false
            resizable: false
            width: tableView.viewport.width * 0.1
            visible: false
        }

        TableViewColumn {
            id: authorColumn
            title: "Name"
            role: "Name"
            movable: false
            resizable: false
            width: tableView.viewport.width
        }

        rowDelegate: Rectangle {
            color: styleData.row % 2 == 0 ? "green" : "yellow"

        }

        model: ArchersModel
    }


}
