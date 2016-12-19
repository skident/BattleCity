import QtQuick 2.5
import QtQuick.Window 2.2
import com.skident.tank 1.0
import com.skident.enemy 1.0
import com.skident.eagle 1.0

Window {
    visible: true
    width: 600
    height: 600
    title: qsTr("Battle City")

    Item
    {
        width: field.width
        height: 200
        anchors.right: field.right

        Rectangle {
            anchors.fill: parent
            objectName: "statistics"
            color: "#adaaaa"

            property alias information: info.text
        }

        Text
        {
            id: info
            font.pixelSize: 20
        }
    }

    Field {
        id: field
        color: "black"
        anchors.centerIn: parent
//        focus: true
//        Keys.onPressed: {

//            switch (event.key)
//            {
//            case Qt.Key_Down:
//            case Qt.Key_Up:
//            case Qt.Key_Left:
//            case Qt.Key_Right:
//            case Qt.Key_Space:
//                player.keyPressed(event.key);
//                break;
//            }
//        }

        Level_1 {}



        Rectangle
        {
            objectName: "game_over"
            id: game_over
            anchors.fill: parent
            color: "black"
            opacity: 0.5
            z: 2
            visible: false

            property alias info: description.text

            Text{
                id: title
                anchors.fill: parent.fill
                color:"white"
                text: "Game over"
                font.pixelSize: 60
                anchors.centerIn: parent
            }
            Text{
                objectName: "reason"
                id: description
                anchors.fill: parent.fill
                color:"white"
                text: "desc"
                font.pixelSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: title.bottom
            }
            Text{
                anchors.fill: parent.fill
                color:"white"
                text: "Press Esc for restart"
                font.pixelSize: 20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: description.bottom
            }


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Restart")
                }
            }
        }

//        EnemyTank {}
//        EnemyTank {}
//        EnemyTank {}

//        Player { id: player}
    }
}
