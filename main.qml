import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Rectangle {
        id: rec
        anchors.centerIn: parent
        width: 100
        height: 100
        radius: 50
        color: "red"
    }
}
