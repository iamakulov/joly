import QtQuick 2.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window {
    id: window
    color: "transparent"

    width: 600 * 1.5
    height: 400 * 1.5
    x: Screen.width / 2 - window.width / 2
    y: Screen.height * 0.3

    flags: Qt.FramelessWindowHint

    Item {
        id: searchFieldContainer

        width: parent.width
        height: 115 * 1.5

        ShadowContainer {
            anchors.fill: parent

            SearchField {
                id: searchField
                objectName: "searchField"

                anchors.fill: parent

                focus: true
                placeholder: "Type to search"

                completer: completer
            }
        }
    }

    Item {
        id: completerContainer

        width: parent.width
        height: 300 * 1.5

        anchors.top: searchFieldContainer.bottom
        anchors.topMargin: -40 * 1.5

        ShadowContainer {
            anchors.fill: parent

            Completer {
                id: completer
                objectName: "completer"

                anchors.fill: parent

                model: actionsModel
            }
        }
    }
}
