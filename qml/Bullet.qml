import QtQuick 2.0
import com.skident.bullet 1.0

BulletCpp {
    objectName: "bullet"
    width: 10
    height: 10

    property alias color : bullet_sprite.color


    Rectangle {
        id: bullet_sprite
        width: parent.width
        height: parent.height
        color: "red"
        visible: true

        Explosion { x: 0; y:0; playing: false; visible: false}
    }
}
