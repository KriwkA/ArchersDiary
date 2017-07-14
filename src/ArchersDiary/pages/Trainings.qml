import QtQuick 2.0

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

Page {
    ListView {
        id: trainingListView
        anchors.fill: parent
        currentIndex: -1

        function toDateString( value ) {
            var date = new Date( 0 );
            date.setUTCSeconds( value );
            return Qt.formatDateTime( date, "dd.MM.yyyy hh:mm:ss");
        }

        delegate: ItemDelegate {
            width: trainingListView.width
            highlighted: ListView.isCurrentItem

            text:  trainingListView.toDateString( model.Date );


            onClicked: {
                trainingListView.currentIndex = index;
            }
        }


        ColumnLayout {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            RemoveButton {
                onClicked: {
                    if( trainingModel.removeRow( trainingListView.currentIndex ) )
                        trainingListView.currentIndex = -1;
                }
                visible: trainingListView.currentIndex !== -1
            }

            AddButton {
                onClicked: {
                    trainingModel.addTraining();
                }
            }

        }

        model: trainingModel
    }
}
