import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0

import "elements"

ApplicationWindow {    
    id: window
    visible: true
    width: 720 / 2
    height: 1280 / 2
    title: qsTr("Archer's Diary")

    Settings {
        id: settings
        property string style: "Default"
    }

    header: ToolBar {

        Material.foreground: "white"

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: pages.depth > 1 ? "images/back.png" : "images/drawer.png";
                }

                onClicked: {        
                    if( pages.depth > 1 ){
                        pages.pop()
                    } else {
                        archerListDrawer.open()
                    }
                }
            }

            Label {
                id: titleLabel
                text: "Diary"
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

            }
        }
    }

    Drawer {
        id: archerListDrawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: parent.height

        ColumnLayout {

            anchors.fill: parent

            Label {
                id: selectArcherLabel
                text: "Select Archer"
                font.pixelSize: 20
                height: 25
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }


            ListView {
                id: archerList

                Layout.fillWidth: true
                height: parent.height - selectArcherLabel.height

                model: archersModel
                onModelChanged: model.select();
                currentIndex: -1

                delegate: ItemDelegate {
                    width: parent.width
                    text: Name
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        archerList.currentIndex = index
                        archerListDrawer.close()
                        arrowsModel.archerID = Id
                    }
                }

                AddButton {
                    parent: archerList
                    x : parent.width - width - 20
                    y : parent.height - height - 20
                    onClicked: {
                        addArcherDialog.open()
                    }
                }

            }
        }

        Dialog {
            id: addArcherDialog

            x: (window.width - width) / 2
            y: (window.height - height) / 2

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
                archersModel.addArcher(archerNameInput.text);
                archersModel.select();
                archerNameInput.text = "";
            }
        }
    }

    StackView {
        id: pages
        anchors.fill: parent

        initialItem: ListView {
            id: menu

            delegate: ItemDelegate {
                width: menu.width
                text: model.title
                onClicked: {
                    var canOpenPage = false;
                    if( model.title === "Arrows" ) {
                        if( arrowsModel.archerID >= 0 ) {
                            arrowsModel.select();
                            canOpenPage = true;
                        } else {
                            archerListDrawer.open();
                        }
                    }

                    if( canOpenPage )
                        pages.push( model.source );
                }
            }

            model: ListModel {
                ListElement { title: "Bows";  }
                ListElement { title: "Arrows"; source: "qrc:/pages/Arrows.qml"}
                ListElement { title: "Scopes"; }
                ListElement { title: "Trainings"; }
                ListElement { title: "Records"; }
                ListElement { title: "Stats"; }
            }
        }
    }

}
