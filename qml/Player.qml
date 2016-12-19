import QtQuick 2.0
import com.skident.tank 1.0

PlayerCpp {
    id: player
    objectName: "player"
    width: 36
    height: 36

    Image {
        source: "sprites/tank_new.png"
        width: parent.width
        height: parent.height
    }
    Component.onCompleted: player.init()
}
