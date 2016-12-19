import QtQuick 2.0
import com.skident.enemy 1.0

EnemyCpp {
    id: enemy
    objectName: "enemy"
    width: 36
    height: 36

    Image {
        source: "sprites/enemy.png"
        width: parent.width
        height: parent.height
    }

    Component.onCompleted: enemy.init()
}
