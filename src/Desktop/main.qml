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
import "dialogs"



ApplicationWindow {    
    property string title_DEFAULT_TEXT : "Diary";

    Material.theme: Material.System

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

        RowLayout {
            id: toolBarRowLayout;

            spacing: 20
            anchors.fill: parent                      

            ToolButton {                
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: pages.depth > 1 ? "img/images/back.png" : "img/images/menu.png"
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
                Material.foreground: "white"
                id: titleLabel
                text: title_DEFAULT_TEXT
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
                    source: "img/images/settings.png"
                }                
            }

        }
    }

    Drawer {
        id: archerListDrawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: parent.height

        ListView {
            id: archerList
            model: archersModel
            onModelChanged: model.select();
            currentIndex: -1
            anchors.fill: parent

            header: ToolBar {

                width: parent.width
                z: 2
                Label {
                    Material.foreground: "white"
                    text: "Select Archer"
                    font.pixelSize: 20
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    anchors.fill: parent
                }
            }
            headerPositioning: ListView.OverlayHeader

            delegate: ItemDelegate {
                width: parent.width
                text: Name
                highlighted: ListView.isCurrentItem
                onClicked: {
                    archerList.currentIndex = index
                    archerListDrawer.close()
                    arrowsModel.archerID = Id
                }

                onPressAndHold: {
                    archerEditDialog.name = Name
                    archerEditDialog.open()
                }
            }

            ImageButton {
                parent: archerList
                x : parent.width - width - 20
                y : parent.height - height - 20
                onClicked: {
                    archerEditDialog.open()
                }
                imgSrc: "img/images/plus.png"
            }

        }

        ArcherEditDialog {
            id: archerEditDialog
            x: (window.width - width) / 2
            y: (window.height - height) / 2
            onAccepted: {                
                archersModel.addArcher( archerEditDialog.name );
                archersModel.select();
                archerEditDialog.name = "";
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
                            titleLabel.text = "Arrows";
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
                ListElement { title: "Arrows"; source: "pages/Arrows.qml" }
                ListElement { title: "Scopes"; }
                ListElement { title: "Trainings"; }
                ListElement { title: "Records"; }
                ListElement { title: "Stats"; }
            }
        }

        onDepthChanged: {
            if(pages.depth === 1)
                titleLabel.text = title_DEFAULT_TEXT;
        }

    }

}
