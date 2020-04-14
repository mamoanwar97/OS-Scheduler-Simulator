import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle {
    anchors.fill: parent
    color: "#313131"

    Rectangle {
        // color of grid background
        color: parent.color
        border.color: "white"
        property string gridColor: border.color
        property string textColor: border.color



        id:root
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width -50
        height: parent.height -50
        property  double totalTime: Scheduler.maxTime()+2;
        property  int numProcess: Scheduler.noOfProcess();

        MouseArea {anchors.fill: parent ;onClicked:{
            var process_out = Scheduler.getProcessesQml();
            root.drawProcesses(process_out);
            }
        }

        Component.onCompleted: {
//            addProcess(0,3,0,3);
//            addProcess(1,2,2,4);
//            addProcess(3,1,1,1);
//            root.totalTime = 10;
//            root.numProcess = 2;
        }

        function addProcess(process,x,y,brust_time) {
            var component = Qt.createComponent("Process.qml");
            var proc = component.createObject(root,
                                   {
                                       grid_x:x,
                                       grid_y:y,
                                       name : process,
                                       time: brust_time
                                   });
        }

        function drawProcesses(process_out) {
            for( var i = 0 ; i < process_out.length; i++) {
//                console.log("draw:",process_out[i].getID(),process_out[i].getTime(),process_out[i].getStart());
                addProcess("P"+process_out[i].getID(),process_out[i].getStart(),process_out[i].getID(),process_out[i].getTime());
            }
        }



        Grid{
            id : verticalLines
            anchors.fill:parent
            columns: root.totalTime
            spacing: root.width/ root.totalTime -1
            Repeater {
                model: root.totalTime;
                Rectangle {
                    Text {
                        anchors.top: parent.bottom
                        color: root.textColor
                        text: index
                    }
                    color: root.gridColor
                    width:1;
                    height:parent.height
                }
            }
        }
        Grid
        {
            id : horizontalLines
            anchors.fill:parent
            rows: root.numProcess
            spacing: root.height/ (root.numProcess) -1
            Repeater {
                model: root.numProcess;
                Rectangle {
                    Text {
                        anchors.right: parent.left
                        color: root.textColor
                        text: "P"+index
                    }
                    color: root.gridColor
                    border.width: 2
                    width:parent.width;
                    height:1
                }
            }
        }
    }

    Connections {
        target: Scheduler
        onSendProcesses : {
            root.totalTime = Scheduler.maxTime()+2;
            root.numProcess= Scheduler.noOfProcess();
            console.log("received Processes: ", processes);
            var process_out = processes;
            root.drawProcesses(process_out);
        }
    }
}
