import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

FocusScope {
    id: scope

    property var completer
    property alias placeholder: field.placeholderText
    property alias text: field.text

    signal input(string text)

    TextField {
        id: field

        anchors.fill: parent
        focus: true
        style: TextFieldStyle {
            background: Rectangle {
                radius: 3
                color: Qt.rgba(0, 0, 0, 0.6)
            }
            placeholderTextColor: "#aeaeae"
            textColor: "#ececec"
        }

        onTextChanged: {
            scope.input(text);
        }

        onAccepted: {
            completer.launchActiveAction();
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
