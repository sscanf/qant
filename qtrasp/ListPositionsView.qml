import QtQuick 2.0

Item{
    id:root
    property alias mmodel: grid.model
    width: 500

    GridView {
        id                  : grid
        anchors.fill        : parent
        cellWidth           : root.width
        cellHeight          : 12
        visible             : true
//        model               : model

        header              :
            Component {
                    Rectangle{
                        color   : "white"
                        width   : root.width
                        height  : 12
                        Row{
                            spacing : 10
                            clip    : true
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'Hora'     }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'Azimut'    }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'Elevación' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'UT' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'RA' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'DEC' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'Top RA' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'Top DEC' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'LST' }
                            Text {  font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'HA' }
                        }
                    }
        }

        delegate :
            Component {
                    Rectangle{
                        width   : root.width
                        height  : 12
                        color: (index==2) ? "blue" : "black"
                        Row{
                            spacing: 10

                            Text { color: "white"; font.pointSize: 8; horizontalAlignment: Text.AlignHCenter; text: 'Azimut'    }
                            Text { color: "white"; font.pointSize: 8; text: pad(model.hour,2)+":"+pad(model.minute,2) }
                            Text { color: "green"; font.pointSize: 8; text: model.az.toFixed(2) }
                            Text { color: "green"; font.pointSize: 8; text: model.el.toFixed(2) }
                            Text { color: "white"; font.pointSize: 8; text: model.ut.toFixed(2) }
                            Text { color: "white"; font.pointSize: 8; text: model.ra.toFixed(2) }
                            Text { color: "white"; font.pointSize: 8; text: model.dec.toFixed(2)}
                            Text { color: "white"; font.pointSize: 8; text: model.topRa.toFixed(2)}
                            Text { color: "white"; font.pointSize: 8; text: model.topDec.toFixed(2)}
                            Text { color: "white"; font.pointSize: 8; text: model.lst.toFixed(2) }
                            Text { color: "white"; font.pointSize: 8; text: model.ha.toFixed(2) }
                        }
                    }
        }
    }
}

