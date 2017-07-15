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

            HeaderToolButton {
                source: "../" + ( pages.depth > 1 ? BackImage : MenuImage );
                onClicked: {        
                    if( pages.depth > 1 )
                        pages.pop()
                    else
                        archerListDrawer.open()                    
                }
            }

            HeaderLabel {
                id: titleLabel
                text: title_DEFAULT_TEXT                
            }

            HeaderToolButton {
                source: "../" + SettingsImage;
            }

        }
    }

    ArcherEditDrawer {
        id: archerListDrawer
        dragMargin: pages.depth === 1 ? Qt.styleHints.startDragDistance : 0
        width: Math.min(window.width, window.height) / 3 * 2
        height: parent.height        
    }

    StackView {
        id: pages
        anchors.fill: parent        

        initialItem: ListView {
            id: menu

            delegate: ItemDelegate {                
                width: menu.width
                text: title
                enabled: {
                    var enable = false;                    
                    switch( text ) {
                    case "Bows" : enable = bowsModel.archerID !== -1; break;
                    case "Arrows" : enable = arrowsModel.archerID !== -1; break;
                    case "Scopes" : enable = scopesModel.bowID !== -1; break;
                    case "Trainings" : enable = trainingModel.archerID !== -1; break;
                    }
                    enable;
                }

                onClicked: {
                    pages.push( model.source );                    
                    switch( text ) {
                    case "Bows" : bowsModel.select(); break;
                    case "Arrows" : arrowsModel.select(); break;
                    case "Scopes" : scopesModel.select(); break;
                    case "Trainings" : trainingModel.select(); break;
                    }
                    titleLabel.text = text;
                }
            }

            model: ListModel {
                ListElement { title: "Bows"; source: "pages/Bows.qml"; }
                ListElement { title: "Arrows"; source: "pages/Arrows.qml"; }
                ListElement { title: "Scopes"; source: "pages/Scopes.qml"; }
                ListElement { title: "Trainings"; source: "pages/Trainings.qml"; }
            }
        }

        onDepthChanged: {
            if(pages.depth === 1)
                titleLabel.text = title_DEFAULT_TEXT;
        }

    }

}
