import QtQuick 2.0
import QtGraphicalEffects 1.0



Rectangle {

    property alias text : text1.text
    property alias image: image.source

    id                  : rectangle1
    width               : 150
    height              : 100
    color               : "#000000"
    radius              : 14
    border.width        : 4
    border.color        : "#07736d"
    clip                : true

    Text {
        id              : text1
        anchors.centerIn: parent
        color           : "#ffffff"
        text            : qsTr("")
        font.bold       : false
        font.pixelSize  : parent.height*.3
    }

    Image {
        id                  : image
        anchors.rightMargin : 8
        anchors.bottomMargin: 8
        anchors.leftMargin  : 8
        anchors.topMargin   : 8
        anchors.fill        : parent
        source              : ""
    }

    states: [
        State {
            name: "pushed"
        }
    ]
}

