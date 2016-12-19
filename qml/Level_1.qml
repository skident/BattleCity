import QtQuick 2.0

Item
{
    id: container
    Component.onCompleted:
    {
        var positions = [
                    "                          ",
                    "                          ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx          xx  xx  ",
                    "  xx  xx          xx  xx  ",
                    "          xx  xx          ",
                    "          xx  xx          ",
                    "    xxxx          xxxx    ",
                    "    xxxx          xxxx    ",
                    "          xx  xx          ",
                    "          xxxxxx          ",
                    "  xx  xx  xxxxxx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx  xx  xx  xx  xx  ",
                    "  xx  xx          xx  xx  ",
                    "  xx  xx          xx  xx  ",
                    "  xx  xx          xx  xx  ",
                    "  xx  xx   xxxx   xx  xx  ",
                    "           xW x           ",
                    "           x  x           "
                ];

        var obstacle = Qt.createComponent("Brick.qml");
        var eagle = Qt.createComponent("Eagle.qml");
        var object;
        var cellSize = 20

        for (var posI = 0; posI < positions.length; posI++)
        {
            var row = positions[posI];
            for (var posJ = 0; posJ < row.length; posJ++)
            {
                if (row[posJ] === ' ')
                    continue;

                if (row[posJ] === 'x')
                {
                    object = obstacle.createObject(container);
                }
                else if (row[posJ] === 'W')
                {
                    object = eagle.createObject(container);
                }

                object.x = posJ * cellSize;
                object.y = posI * cellSize;
            }
        }
    }
}
