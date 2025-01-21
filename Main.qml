import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example.dbus 1.0

ApplicationWindow {
    id:window1
    visible: true
    width: 640
    height: 480
    title: "App1 - Sender and Listener"
    property string inputMessage: ""
    color: "lightgreen"

    DbusInterface {
        id: dbusInterface
    }

    Column {
        spacing: 20
        anchors.centerIn: parent

        TextArea {
            id: messageArea
            height: 200
            width: 300
            text: "Messages will appear here..."
            readOnly: true
        }

        TextField {
            id: inputField
            height: 50
            width: 300
            placeholderText: "Enter message"
            text: inputMessage
            onTextChanged: inputMessage = text
        }

        Button {
            text: "Send"
            onClicked: {
                dbusInterface.sendMessageToApp1(inputMessage)
                messageArea.text += "\nApp1: " + inputMessage
                inputField.text = ""
            }
        }

        // Listen for messages from App2
        Connections {
            target: dbusInterface
            function onMessageReceivedFromApp1(message) {
                messageArea.text += "\nApp2: " + message
                window1.color = message
            }
        }
    }
}
