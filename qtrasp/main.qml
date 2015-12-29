import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import ea3um.laboratory.moon 1.0
import ea3um.laboratory.sun 1.0

Window {

    visible : true
    id : mainScreen
    color: "black"
    title: "Moon Tracker"
    width: 800
    height: 600

    function pad (num, size) {
        var s = "000000000" + num;
        return s.substr(s.length-size);
    }

    function csize(y){
        var sz = (y*y)/3*10*2
        return sz;
    }

    SunModel{
        id: sun
    }

    MoonModel{
        id: moon
        Component.onCompleted:{
            moon.setQTH(1.96 ,41.27);
        }
    }

    GridLayout {

        id                  : layout
        width               : 1024
        height              : 768
        rowSpacing          : 5
        rows                : 2
        anchors.rightMargin : 0
        anchors.bottomMargin: 0
        anchors.leftMargin  : 0
        anchors.topMargin   : 0
        visible             : true
        anchors.fill        : parent
        columns             : 3
        //        spacing: 6

        Rectangle
        {
            id      : azimuth
            width   : 649
            radius  : 10
            gradient: Gradient {
                GradientStop { position: 0; color: "#07736d" }
                GradientStop { position: 1; color: "#101313" }
            }

            Layout.fillWidth        : true
            Layout.fillHeight       : true
            Layout.minimumWidth     : 50
            Layout.preferredWidth   : 50
            Layout.preferredHeight  : 50

            //color : "black"

            CircularGauge {
                property real randVal   : 0;

                id          : gauge3
                value       : accelerating ? randVal: 0
                minimumValue: 0
                maximumValue: 360
                stepSize    : 1
                anchors.fill: parent
                style       : AzimutGaugeStyle {
                    tickmarkLabel: Text {
                        color: "green"
                        visible: styleData.value === 0   ||
                                 styleData.value === 45  ||
                                 styleData.value === 90  ||
                                 styleData.value === 135 ||
                                 styleData.value === 180 ||
                                 styleData.value === 225 ||
                                 styleData.value === 270 ||
                                 styleData.value === 315

                        font.pixelSize: (styleData.value === 0 ) ? toPixels(0.2) :  styleData.value === 90  ? toPixels(0.2) : styleData.value === 180 ? toPixels(0.2) :
                                         styleData.value === 270 ? toPixels(0.2) : toPixels(0.1)

                        text: (styleData.value === 0 )   ? "N"   : styleData.value === 45    ? "NE" : styleData.value === 90    ? "E"  :
                               styleData.value === 135   ? "SE"  : styleData.value === 180   ? "S"  : styleData.value === 225   ? "SO" :
                               styleData.value === 270   ? "O"   : styleData.value === 315   ? "NO" : ""
                    }
                }

                property bool accelerating: false
                x: 0
                y: 303
                z: 0
                anchors.rightMargin : 0
                anchors.bottomMargin: 0
                anchors.leftMargin  : 0
                anchors.topMargin   : 0
                antialiasing        : false
                rotation            : 0
                scale               : 1

                Keys.onSpacePressed : {

                    if (event.isAutoRepeat)
                        return;

                    accelerating = true
                    if (randVal===0){
                        randVal = Math.random()* maximumValue
                    }
                }

                Keys.onReleased : {

                    if (event.isAutoRepeat)
                        return;

                    if (event.key === Qt.Key_Space) {
                        console.log ("pulsando");
                        accelerating = false;
                        event.accepted = true;
                        randVal = 0;
                    }
                }

                Component.onCompleted: forceActiveFocus()

                Behavior on value {
                    NumberAnimation {
                        duration     : 1300
                        easing.type  : Easing.OutSine
                        easing.period: 1.5
                        //easing.amplitude: Math.min(Math.max(-130, gauge3.value*2.2 - 130), 133)
                    }
                }
            }
        }

        Rectangle {
            id                      : elevacion
            radius                  : 10
            Layout.fillWidth        : true
            Layout.fillHeight       : true
            Layout.minimumWidth     : 50
            Layout.preferredWidth   : 50
            Layout.preferredHeight  : 50
            gradient: Gradient {
                GradientStop { position: 0; color: "#07736d" }
                GradientStop { position: 1; color: "#101313" }
            }

            CircularGauge {
                property real randVal   : 0;
                antialiasing: false

                id          : elev
                value       : 0
                minimumValue: -30
                maximumValue: 210
                stepSize    : 1
                anchors.fill: parent

                style       : AzimutGaugeStyle {
                    minimumValueAngle   : -100
                    maximumValueAngle   : 100
                    minimumWarning      : 0
                    maximumWarning      : 90
                    halfGauge           : false
                    labelStepSize       : 20

                    tickmarkLabel       : Text {
                        color           : "green"
                        font.pixelSize  : toPixels(0.1)
                        text            : styleData.value
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth            : true
            Layout.fillHeight           : true
            Layout.rowSpan              : 3
            Layout.minimumWidth         : 40
            width                       : parent.width
            color                       : "green"
        }

        Rectangle {
            id                          : panelAzimut
            Layout.fillWidth            : true
            Layout.fillHeight           : true
            Layout.columnSpan           : 1
            width                       : parent.width
            height                      : 10
            color                       : "black"

            Row {
                anchors.centerIn: parent
                spacing:    2

                PanelButton {
                    id              : azimMas
                    width           : panelAzimut.width*0.2
                    height          : panelAzimut.height
                    anchors.bottom  : panelAzimut.bottom
                    text            : "+"
                }

                PanelButton {
                    id              : azimStop
                    width           : panelAzimut.width*0.2
                    height          : panelAzimut.height
                    anchors.bottom  : panelAzimut.bottom
                    text            : "Stop"
                }

                PanelButton {
                    id              : azimMenos
                    width           : panelAzimut.width*0.2
                    height          : panelAzimut.height
                    anchors.bottom  : panelAzimut.bottom
                    text            : "-"
                }

                PanelButton {
                    id              : azimManual
                    width           : panelAzimut.width*0.2
                    height          : panelAzimut.height
                    anchors.bottom  : panelAzimut.bottom
                    image            : "numeric_keypad.png"
                }
            }
        }

        Rectangle {
            id                          : panelElev
            Layout.fillWidth            : true
            Layout.fillHeight           : true
            Layout.columnSpan           : 1
            width                       : parent.width
            height                      : 10
            color                       : "black"

            Row {
                anchors.centerIn: parent
                spacing:    2

                PanelButton {
                    id              : elevMas
                    width           : panelAzimut.width*0.2
                    height          : panelElev.height
                    anchors.bottom  : panelElev.bottom
                    text            : "+"
                }

                PanelButton {
                    id              : elevStop
                    width           : panelAzimut.width*0.2
                    height          : panelElev.height
                    anchors.bottom  : panelElev.bottom
                    text            : "Stop"
                }

                PanelButton {
                    id              : elevMenos
                    width           : panelAzimut.width*0.2
                    height          : panelElev.height
                    anchors.bottom  : panelElev.bottom
                    text            : "-"
                }

                PanelButton {
                    id              : elevManual
                    width           : panelAzimut.width*0.2
                    height          : panelElev.height
                    anchors.bottom  : panelElev.bottom
                    image            : "numeric_keypad.png"
                }
            }
        }


        Rectangle{
            Layout.fillWidth            : true
            Layout.fillHeight           : true
            Layout.columnSpan           : 2
            Layout.minimumHeight        : 50
            width                       : parent.width
            color                       : "black"
            clip                        : true

            Flipable {
                property bool flipped   : false
                id                      : flipable
                anchors.fill            : parent

                front:
                    Rectangle{
                        anchors.fill: parent
                        color       : "black"
                        Image {
                            id                  : moonImage
                            anchors.left        : parent.left
                            anchors.top         : parent.top
                            source              : "moon.png"
                        }

                        ListPositionsView{
                            id                  : gridMoon
                            mmodel              : moon
                            anchors.bottom      : parent.bottom
                            anchors.left        : moonImage.right
                            anchors.top         : parent.top
                            clip                : true
                        }
                }

                back:
                    Rectangle{
                        color       : "black"
                        anchors.fill: parent
                        Image{
                            id                  : sunImage
                            anchors.left        : parent.left
                            anchors.top         : parent.top
                            source              : "sun.png"
                        }

                        ListPositionsView{
                            id                  : gridSun
                            mmodel              : sun
                            anchors.bottom      : parent.bottom
                            anchors.left        : sunImage.right
                            anchors.top         : parent.top
                            clip                : true
                        }
                }

                    transform: Rotation {
                        id: rotation
                        origin.x: flipable.width/2
                        origin.y: flipable.height/2
                        axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
                        angle: 0    // the default angle
                    }

                    states: State {
                        name: "back"
                       PropertyChanges { target: rotation; angle: 180 }
                        when: flipable.flipped
                    }
                    transitions: Transition {
                        NumberAnimation { target: rotation; property: "angle"; easing.type: Easing.OutElastic; duration: 4000 }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: flipable.flipped = !flipable.flipped
                    }
            }
        }
    }

    //qDebug() << hour << minute << RA << Dec << topRA << topDec << LST << HA << Az << El << dist;

    PanelButton {
        id      : panelButton1
        width   : 70
        height  : 50
        anchors.bottom  : parent.bottom
        anchors.left    : parent.left
    }
/*
    PanelButton {
        id          : panelButton2
        anchors.left: panelButton1.right
        anchors.bottom  : parent.bottom
        height      : 90
    }

    PanelButton {
        id          : panelButton3
        anchors.left: panelButton2.right
        anchors.bottom  : parent.bottom
        height      : 90
    }

    PanelButton {
        id          : panelButton4
        anchors.left: panelButton3.right
        anchors.bottom  : parent.bottom
        height      : 90
    }*/
}

