import QtQuick 2.9
import QtQuick.Controls 2.2

ListView {
    property int circlCount: 10;
    property int shotScore: -1
    currentIndex: shotScore == -1 ? -1 : 10 - shotScore;

    id: scoreList


    model: ListModel {
        ListElement { score: "10";    color: "yellow"; }
        ListElement { score: "9";     color: "yellow"; }
        ListElement { score: "8";     color: "red";    }
        ListElement { score: "7";     color: "red";    }
        ListElement { score: "6";     color: "blue";   }
        ListElement { score: "5";     color: "blue";   }
        ListElement { score: "4";     color: "black";  }
        ListElement { score: "3";     color: "black";  }
        ListElement { score: "2";     color: "white";  }
        ListElement { score: "1";     color: "white";  }
        ListElement { score: "M";     color: "white";  }
    }

    delegate: ItemDelegate {
        width: parent.width
        highlighted: ListView.isCurrentItem
        visible: circlCount > 10 - score || score === "M"
        text: score
        onClicked: {
            scoreList.shotScore = score !== "M" ? score : 0;
        }
    }
}
