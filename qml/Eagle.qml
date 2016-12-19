import QtQuick 2.0
import com.skident.eagle 1.0

EagleCpp {
    objectName: "eagle"
    width: 38
    height: 38

    Image {
        id: eagle_sprite
        source: "sprites/eagle.png"
        width: parent.width
        height: parent.height
    }

    states: [
        State {
           name: "default"
           PropertyChanges { target: eagle_sprite; source: "sprites/eagle.png" }
        },
        State {
           name: "dead"
           PropertyChanges { target: eagle_sprite; source: "sprites/stone.png" }
        }
    ]
}
