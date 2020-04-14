import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.1

Window {
    id : main
    visible: true
    width: 1800
    height: 1000
    color: "transparent"
    property real preemtive: 0
    property string mode: "none"

    Rectangle {
        id: centerRectangle
        width: parent.width * 0.6
        height: parent.height * 0.8
        color: "#111"
        anchors.centerIn: parent
        radius: 20

        Rectangle{
            id: monitor
            width: centerRectangle.width * 0.83
            height: centerRectangle.height * 0.80
            color: "#888"
            anchors.centerIn: centerRectangle

            Chart
            {
                id:chart
            }

//            Text {
//                id: monitor_text
//                text: "View"
//                anchors.centerIn: parent
//                font.pointSize: 10
//                color: "white"
//            }
        }


        RectangularGlow {
            id: mini_btn_effect
            anchors.fill: start_btn
            glowRadius: 10
            spread: 0.2
            color: "#bcf4af"
            cornerRadius: 20

        }
        Rectangle{
            id: start_btn
            width: monitor.width * 0.2
            height: 50 * 0.8
            color: "#0c2806"
            anchors.bottom: monitor.top
            anchors.left: monitor.left
            anchors.bottomMargin: 15
            radius: 10
            opacity: 0.85
            Text {
                text: "START"
                font.pointSize: 12
                color: "white"
                anchors.centerIn: parent
            }
        }
        MouseArea {
            anchors.fill: start_btn
            hoverEnabled: true
            onEntered: start_btn.opacity = 1;
            onExited:  start_btn.opacity =0.85;
            onClicked: {main.start();}
        }
        MouseArea {
            anchors.fill: reset_btn
            hoverEnabled: true
            onEntered: reset_btn.opacity = 1;
            onExited:  reset_btn.opacity =0.85;
            onClicked: {main.reset();}
        }

        RectangularGlow {
            anchors.fill: reset_btn
            glowRadius: 10
            spread: 0.2
            color: "#fd9cc2"
            cornerRadius: 20

        }
        Rectangle{
            id: reset_btn
            width: monitor.width * 0.2
            height: 50 * 0.8
            color: "#550222"
            radius: 10
            anchors.bottom: monitor.top
            anchors.right: monitor.right
            anchors.bottomMargin: 15
            Text {
                text: "RESET"
                font.pointSize: 12
                color: "white"
                anchors.centerIn: parent
            }
        }
        Switch {
            id: preemmtive_switch
            anchors.bottom: monitor.top
            anchors.bottomMargin: 10
            anchors.right: monitor.horizontalCenter
            onClicked: {
                if(preemmtive_switch.checked)
                    preemtive = 1
                else
                    preemtive = 0
            }
        }
        Text{
            text: "Preemtive"
            color: "#fff"
            anchors.left: preemmtive_switch.right
            anchors.verticalCenter: preemmtive_switch.verticalCenter
            font.pointSize: 15

        }

        Rectangle{
            id: preemmtive_box
            width: monitor.width * 0.3
            height: 50 * 0.8
            color: "#111"
            anchors.top: monitor.bottom
            anchors.left: monitor.left
            anchors.topMargin: 15
            Text {
                id: average_waiting
                text: "Average Waiting: " + Scheduler.averageWaitingTime()
                font.pointSize: 15
                color: "white"
                anchors.centerIn: parent
            }
        }
        Rectangle{
            id: team_name
            width: monitor.width * 0.2
            height: 50 * 0.8
            color: "#111"
            anchors.top: monitor.bottom
            anchors.horizontalCenter: monitor.horizontalCenter
            anchors.topMargin: 15
            Text {
                id: group_no
                text: "Group xx"
                font.pointSize: 20
                color: "white"
                anchors.centerIn: parent
            }
        }
        Rectangle{
            id: process_box
            width: monitor.width * 0.3
            height: 50 * 0.8
            color: "#111"
            anchors.top: monitor.bottom
            anchors.right: monitor.right
            anchors.topMargin: 15
            Text {
                id: current_process
                text: "Current process: None"
                font.pointSize: 15
                color: "white"
                anchors.centerIn: parent
            }
        }
    }

    Rectangle {
        id: leftRectangle
        width: parent.width * 0.1
        height: parent.height * 0.6
        color: "#111"
        anchors.right: centerRectangle.left
        anchors.verticalCenter: centerRectangle.verticalCenter
    }

    Rectangle {
        id: rightRectangle
        width: parent.width * 0.1
        height: parent.height * 0.6
        color: "#111"
        anchors.left: centerRectangle.right
        anchors.verticalCenter: centerRectangle.verticalCenter
    }

    Rectangle {
        id: rightCircle
        width: rightRectangle.width * 1.6
        height: rightRectangle.height
        radius: rightCircle.height * 0.7
        color: "#111"
        anchors.verticalCenter: rightRectangle.verticalCenter
        anchors.horizontalCenter: rightRectangle.right
    }

    Rectangle {
        id: leftCircle
        width:  leftRectangle.width * 1.6
        height: leftRectangle.height
        radius: leftCircle.height * 0.5
        color: "#111"
        anchors.verticalCenter:   leftRectangle.verticalCenter
        anchors.horizontalCenter: leftRectangle.left
    }

    Rectangle
    {
        id: inputs_rect
        width: 250
        height: 250
        border.color: "#666"
        border.width: 5
        radius: width*0.5
        anchors.centerIn: leftRectangle
        color: leftRectangle.color
    }
    RectangularGlow {
        id: input_effect
        anchors.fill: arrival_input
        glowRadius: 10
        spread: 0.2
        color: "#ccc"
        cornerRadius: 20

    }
    TextField {
        id: arrival_input
        width: inputs_rect.width * 0.4
        placeholderText: "Arrival time"
        anchors.verticalCenter: inputs_rect.top
        anchors.horizontalCenter: inputs_rect.horizontalCenter
        font.pointSize: 8
        height: 50
    }
    RectangularGlow {
        id : add_process_btn_style
        anchors.fill: add_process_btn
        glowRadius: circle_effect.glowRadius
        spread: circle_effect.spread
        color: circle_effect.color
        cornerRadius: circle_effect.cornerRadius
        opacity: 0.85
    }
    Rectangle
    {
        id: add_process_btn
        width: fcfs_button.width
        height: fcfs_button.height
        color: fcfs_button.color
        radius: fcfs_button.radius
        anchors.verticalCenter: inputs_rect.verticalCenter
        anchors.horizontalCenter: inputs_rect.horizontalCenter
        opacity: 0.85
        Text {
            text: "  Add\nprocess"
            anchors.centerIn: parent
            font.pointSize: 10
            color: "white"
        }
    }

    RectangularGlow {
        anchors.fill: priority_input
        glowRadius: input_effect.glowRadius
        spread: input_effect.spread
        color: input_effect.color
        cornerRadius: input_effect.cornerRadius

    }
    TextField {
        id: priority_input
        enabled: isPriority()
        width: fcfs_button.width
        height: 50
        placeholderText: "Priority"
        anchors.horizontalCenter: inputs_rect.right
        anchors.verticalCenter: inputs_rect.verticalCenter
        font.pointSize: 8
    }
    RectangularGlow {
        anchors.fill: brust_input
        glowRadius: input_effect.glowRadius
        spread: input_effect.spread
        color: input_effect.color
        cornerRadius: input_effect.cornerRadius

    }
    TextField {
        id: brust_input
        width: fcfs_button.width
        placeholderText: "Brust time"
        anchors.horizontalCenter: inputs_rect.left
        anchors.verticalCenter: inputs_rect.verticalCenter
        font.pointSize: 8
        height: 50
    }
    RectangularGlow {
        anchors.fill: timeSlice_input
        glowRadius: input_effect.glowRadius
        spread: input_effect.spread
        color: input_effect.color
        cornerRadius: input_effect.cornerRadius

    }
    TextField {
        id: timeSlice_input
        enabled:isRr()
        width: fcfs_button.width
        placeholderText: "Time Slice"
        anchors.horizontalCenter: inputs_rect.horizontalCenter
        anchors.verticalCenter: inputs_rect.bottom
        font.pointSize: 8
        height: 50
    }

    Rectangle
    {
        id: buttons_rect
        width: 250
        height: 250
        border.color: "#666"
        border.width: 5
        radius: width*0.5
        anchors.centerIn: rightRectangle
        color: rightRectangle.color
    }
    RectangularGlow {
        anchors.fill: fcfs_button
        id: circle_effect
        glowRadius: 5
        spread: 0.5
        color: "#ccc"
        cornerRadius: 50

    }
    Rectangle
    {
        id: fcfs_button
        opacity: 0.85
        width: inputs_rect.width * 0.4
        height: inputs_rect.height * 0.4
        color: "#222"
        radius: width*0.5
        anchors.verticalCenter: buttons_rect.top
        anchors.horizontalCenter: buttons_rect.horizontalCenter
        Text {
            text: "FCFS"
            anchors.centerIn: parent
            font.pointSize: 15
            color: "white"
        }
    }
    RectangularGlow {
        anchors.fill: priority_button
        glowRadius: circle_effect.glowRadius
        spread: circle_effect.spread
        color: circle_effect.color
        cornerRadius: circle_effect.cornerRadius

    }
    Rectangle
    {
        id: priority_button
        opacity: 0.85
        width: fcfs_button.width
        height: fcfs_button.height
        color: fcfs_button.color
        radius: fcfs_button.radius
        anchors.verticalCenter: buttons_rect.bottom
        anchors.horizontalCenter: buttons_rect.horizontalCenter
        border.color: "#5d5d5d"
        border.width: 0.5
        Text {
            text: "Priority"
            anchors.centerIn: parent
            font.pointSize: 15
            color: "white"
        }
    }

    RectangularGlow {
        anchors.fill: rr_button
        glowRadius: circle_effect.glowRadius
        spread: circle_effect.spread
        color: circle_effect.color
        cornerRadius: circle_effect.cornerRadius

    }
    Rectangle
    {
        id: rr_button
        opacity: 0.85
        width: fcfs_button.width
        height: fcfs_button.height
        color: fcfs_button.color
        radius: fcfs_button.radius
        anchors.horizontalCenter: buttons_rect.right
        anchors.verticalCenter: buttons_rect.verticalCenter
        Text {
            text: "Round\nRobin"
            anchors.centerIn: parent
            font.pointSize: 15
            color: "white"
        }
    }

    RectangularGlow {
        anchors.fill: stf_button
        glowRadius: circle_effect.glowRadius
        spread: circle_effect.spread
        color: circle_effect.color
        cornerRadius: circle_effect.cornerRadius

    }
    Rectangle
    {
        id: stf_button
        opacity: 0.85
        width: fcfs_button.width
        height: fcfs_button.height
        color: fcfs_button.color
        radius: fcfs_button.radius
        anchors.horizontalCenter: buttons_rect.left
        anchors.verticalCenter: buttons_rect.verticalCenter
        Text {
            text: "STF"
            anchors.centerIn: parent
            font.pointSize: 15
            color: "white"
        }
    }

    MouseArea {
        anchors.fill: stf_button
        hoverEnabled: true
        onEntered: stf_button.opacity = 1;
        onExited:  stf_button.opacity =0.85;
        onClicked: {
            current_process.text = "Current process: STF";
//            monitor_text.text = ((preemtive)? "preemtive":"non preemtive");
            main.mode  = "STF";
        }
    }
    MouseArea {
        anchors.fill: rr_button
        hoverEnabled: true
        onEntered: rr_button.opacity = 1;
        onExited:  rr_button.opacity =0.85;

        onClicked: {
            current_process.text = "Current process:  Round Robin"
//            monitor_text.text = ((preemtive)? "preemtive":"non preemtive")
            main.mode  = "RoundRobin";
        }
    }
    MouseArea {
        anchors.fill: priority_button
        hoverEnabled: true
        onEntered: priority_button.opacity = 1;
        onExited:  priority_button.opacity =0.85;

        onClicked: {
            current_process.text = "Current process: Priority"
            main.mode  = "Priority";
        }
    }
    MouseArea {
        anchors.fill: fcfs_button
        hoverEnabled: true
        onEntered: fcfs_button.opacity = 1;
        onExited:  fcfs_button.opacity =0.85;

        onClicked: {
            current_process.text = "Current process: FCFS"
//            monitor_text.text = ((preemtive)? "preemtive":"non preemtive")
            main.mode = "FCFS";
        }
    }
    MouseArea {
        anchors.fill: add_process_btn
        hoverEnabled: true
        onEntered: add_process_btn.opacity = 1;
        onExited:  add_process_btn.opacity =0.85;
        onClicked: {
            main.addProcess();
        }
    }

    function addProcess()
    {
        if(brust_input.text === "" || arrival_input.text === "")
        {
            Scheduler.errorMsg("Missing Process Data");
            return;
        }
        else if (priority_input.text=== "" && main.mode === "Priority")
        {
            Scheduler.errorMsg("Missing Process Priority");
            return;
        }

        var brust = parseFloat(brust_input.text );
        var arrival = parseFloat(arrival_input.text);
        var priority = parseFloat(priority_input.text);
        var timeSlice = parseFloat(timeSlice_input.text);
        Scheduler.addProcess(brust,arrival,priority,timeSlice);
    }

    function start()
    {
        if (main.mode  === "Priority")
            Scheduler.startPriority(preemtive);
        else if (main.mode  === "FCFS")
            Scheduler.startFCFS();
        else if (main.mode  === "RoundRobin")
            Scheduler.startRoundRobin();
        else if (main.mode  === "STF")
            Scheduler.startSTF( preemtive);
        else
        {
            Scheduler.errorMsg("Select the Mode");
            console.log("Node Mode");
        }
    }

    function reset()
    {
        console.log("reset");
        current_process.text = "Current process: None"
        main.mode  = "none";

        Scheduler.clear();
        chart.clear();
    }
    function isRr()
    {
        return main.mode  == "RoundRobin"
    }
    function isPriority()
    {
        return main.mode  == "Priority"
    }
}
