import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Component.onCompleted: {
        console.log(height)
        myData.setHeightWindow(height)
    }

    onClosing: {
        myData.stopThreads()
    }

    Rectangle {
        id: rec
        width: 100
        height: 100
        radius: 50
        color: "red"
        x: (parent.width - width) / 2
        y: myData.y
    }
    Row {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        Button {
            anchors.top: parent.top
            text: "Stop"
            onClicked: {
                myData.stopThreads()
            }
        }
        Button {
            anchors.top: parent.top
            text: "Start"
            onClicked: {
                myData.startThreads()
            }
        }

        Button {
            anchors.top: parent.top
            text: "Reset"
            onClicked: {
                myData.resetCoord()
            }
        }
    }


}
