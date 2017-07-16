import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "../elements"
import "../dialogs"

StackPage {
    property int trainingStandardID;

    SwipeView {
        id: standardPages;
        anchors.fill: parent
        Repeater {
            model: standardExcerciseModel.excerciseCount()
            Loader {
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                sourceComponent: Page {
                    id: shotTablePage;

                    function excerciseId() {
                        return standardExcerciseModel.excerciseId( standardPages.currentIndex );
                    }

                    function excerciseName() {
                        return excerciseModel.excerciseName( excerciseId() );
                    }

                    function shotsPerSerie() {
                        return excerciseModel.shotPerSerie( excerciseId() );
                    }

                    function seriesCount() {
                        return excerciseModel.seriesCount( excerciseId() );
                    }


                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 10;
                        Label {
                            Layout.fillWidth: true;
                            height: 32;
                            text: shotTablePage.excerciseName();
                        }


                        Frame {
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;

                            ShotTableView {
                                anchors.fill: parent
                                rowCount: shotTablePage.seriesCount();
                                colCount: shotTablePage.shotsPerSerie();
                            }
                        }
                    }
                }
            }
        }
    }

    PageIndicator {
        count: standardPages.count
        currentIndex: standardPages.currentIndex
        anchors.bottom: standardPages.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
