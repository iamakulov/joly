import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

FocusScope {
    id: container

    property var completer
    property alias placeholder: field.placeholderText
    property alias text: field.text

    signal input(string text)

    Rectangle {
        id: rectangle
        anchors.fill: parent

        border.width: 1
        border.color: "#ccc"
        color: "#fff"
        radius: 4 * 1.5

        TextField {
            id: field

            anchors.fill: parent
            focus: true
            style: TextFieldStyle {
                background: Rectangle {
                    color: "transparent"
                }
                placeholderTextColor: "#999"
                font.pointSize: 32
                font.family: "Segoe UI Light"
            }

            onTextChanged: {
                container.input(text);
            }

            onAccepted: {
                completer.launchActiveAction();
            }
        }
    }

    Keys.onPressed: {
        var eventAccepted = true;

        if (event.key === Qt.Key_Meta || event.key === Qt.Key_Escape)
            userInterface.hide();

        else if (event.key === Qt.Key_Up)
            completer.moveFocusUp();

        else if (event.key === Qt.Key_Down)
            completer.moveFocusDown();

        // Qt.Key_Enter is handled in TextField object.

        else
            eventAccepted = false;

        event.accepted = eventAccepted;
    }
}

/*
    id
    property declarations
    signal declarations
    JavaScript functions
    object properties
    child objects
    states
    transitions
*/
