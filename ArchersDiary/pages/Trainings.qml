import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "../elements"
import "../dialogs"

StackPage {
    title: "Training"    

    ListView {
        id: trainingListView
        anchors.fill: parent
        currentIndex: -1

        function toDateString( value ) {
            var date = new Date( 0 );
            date.setUTCSeconds( value );
            return Qt.formatDateTime( date, "dd.MM.yyyy hh:mm:ss" );
        }

        function setTrainingIdToModels( id ) {
            recordModel.trainingID = id;
            trainingStandardModel.trainingID = id;
            trainingModel.currentTrainingID = id;
        }

        delegate: ItemDelegate {
            width: trainingListView.width
            highlighted: ListView.isCurrentItem

            text: trainingListView.toDateString( model.Date );

            onClicked: {
                trainingListView.currentIndex = index;
                trainingListView.setTrainingIdToModels( Id );                                
                trainingStandardModel.select();
                stackView.title = "Training";
                stackView.push( "Training.qml" );
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
