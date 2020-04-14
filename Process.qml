import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

Rectangle {
    // for centering the rectange
    property double w: root.width/root.totalTime;
    property double h: root.height/root.numProcess;
    property int marginCenter: 3
    // for positioning
    property double grid_x: 5
    property int grid_y: 5
    // style
    property string name: "P1"
    property string textColor: "white"
    property string processColor: "darkCyan"
    // time
    property double time: 1


    width: (  w * time - marginCenter*2 ) ;
    height: h- marginCenter*2;
    x : grid_x * w + marginCenter
    y : grid_y * h+ marginCenter
    color: processColor
    radius: 5
    Text {
        id: txt
        text: parent.name
        anchors.centerIn: parent
        color: parent.textColor
    }


    // colors mlhash 30 lazma
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {

        }

        onEntered : {this.swapColors(); parent.border.width= 2;}
        onExited:   {this.swapColors();   parent.border.width= 0;}

        function swapColors() {
            var temp = parent.processColor;
            parent.processColor = parent.textColor;
            parent.textColor = temp;
        }
    }
}
