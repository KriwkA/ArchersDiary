import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import "../elements"

Dialog {
    title: "Training"
    focus: true
    modal: true

    header: ToolBar {

        RowLayout {
            id: toolBarRowLayout;

            spacing: 20
            anchors.fill: parent

            HeaderToolButton {
                source: "../" + BackImage

                onClicked: {
                    close();
                }
            }

            HeaderLabel {
                id: titleLabel
                text: "Training"
            }

            HeaderToolButton {                
                enabled: false;
            }

        }
    }   

}
