import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0

import com.archersdiary.views.training_calendar 1.0

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
                source: "../" + ( mainWindowPages.depth > 1 ? BackImage : MenuImage );
                onClicked: {        
                    if( mainWindowPages.depth > 1 )
                        mainWindowPages.pop()
                    else
                        archerListDrawer.open()                    
                }
            }

            HeaderLabel {
                id: titleLabel
                text: mainWindowPages.title
            }

            HeaderToolButton {
                source: "../" + AddImage;

                onClicked: {
                    if( mainWindowPages.depth == 1 ) {
                        standardsDrawer.open()
                    }
                }
            }

        }
    }

    ArcherEditDrawer {
        id: archerListDrawer
        dragMargin: mainWindowPages.depth === 1 ? Qt.styleHints.startDragDistance : 0
        width: Math.min(window.width, window.height) / 3 * 2
        height: parent.height
    }

    StandardsDrawer {
        id: standardsDrawer
        dragMargin: 0
        width: Math.min(parent.width, window.height) / 3 * 2
        height: parent.height
    }

    TitleStackView {
        id: mainWindowPages
        anchors.fill: parent

        initialItem: ColumnLayout {
            anchors.fill: parent
            spacing: 0;

            TrainingCalendar {                
                id: calendar
                Layout.fillWidth: true;
                Layout.fillHeight: true;
            }

            ListView {
                id: standardList
                Layout.fillWidth: true;
                Layout.fillHeight: true;

                delegate: ItemDelegate {
                    width: standardList.width
                    highlighted: ListView.isCurrentItem

                    text: standardModel.standardName( Standard );

                    onClicked: {
                        console.log(trainingModel.rowCount());
                        trainingModel.select();
//                        standardList.currentIndex = index;
//                        simpleShotModel.trainingID = Id;
//                        standardExcerciseModel.standardID = Standard;
//                        excerciseModel.select();
//                        mainWindowPages.title = "Standard";
//                        mainWindowPages.push( "pages/StandardPage.qml" );
                    }
                }

                model: trainingModel
            }
        }

//        initialItem: ListView {
//            id: menu

//            delegate: ItemDelegate {
//                width: menu.width
//                text: title
//                enabled: {
//                    switch( text ) {
//                    case "Trainings" : trainingModel.archerID !== -1; break;
//                    }
//                }

//                onClicked: {
//                    switch( text ) {
//                    case "Trainings" : trainingModel.select(); break;
//                    }
//                    mainWindowPages.title = text;
//                    mainWindowPages.push( model.source );
//                }
//            }

//            model: ListModel {
//                ListElement { title: "Trainings"; source: "pages/Trainings.qml"; }
//            }
//        }

        onDepthChanged: {
            if( mainWindowPages.depth === 1 )
                title = title_DEFAULT_TEXT;
        }

    }

}
