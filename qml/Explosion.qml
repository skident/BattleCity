import QtQuick 2.0


AnimatedImage
{
    objectName: "explosion"
    width: 40
    height: 40
    id: animation;
    source: "sprites/explosion.gif";
    playing: false
    visible: false

//    onFrameChanged:
//    {
//        // TODO: find normal gif
//        if ((frameCount-1) === currentFrame)
//        {
////            console.log("stopped animation")
////            animation.playing = false
//            playing = false;
//            explosionAnim.start();
//        }
//    }

    ParallelAnimation
    {
        id:explosionAnim
        NumberAnimation { target: animation; property: "opacity"; from : 1 ;to: 0; duration: 300 }
        NumberAnimation { target: animation; property: "scale"; from : 1 ;to: 0.7; duration: 700 }
        onStopped: {animation.visible = false; animation.scale = 1 ; animation.opacity = 1; }
    }
}
