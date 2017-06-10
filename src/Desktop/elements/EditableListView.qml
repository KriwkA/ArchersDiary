import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1


ListView {
    property bool editable: true;
    property bool removable: true;

    delegate: ItemDelegate {
        id: rowDelegate
        width: parent.width
        highlighted: ListView.isCurrentItem

        RowLayout {
            Text {
                text: Name + "\n" +
                      "Spine: " + Spine + "\n" +
                      "Length: " + Length + " mm.\n" +
                      "Diameter: " + Diameter + " mm.";
                Layout.fillWidth: true;
            }
            ImageButton {
                id: editButton;
                enabled: editable;
                visible: editable;
            }
            ImageButton {
                id: removeButton;
                enabled: editable;
                visible: editable;
            }
        }
    }
}


