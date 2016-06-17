import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

Window {
    id: window

    title: "Joly"

    visible: false

    // Background
    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "image://Background/latestScreenshot"
        cache: false
    }

    GaussianBlur {
        id: imageBlur
        anchors.fill: image
        source: image
        radius: 8
        samples: 16
    }

    BrightnessContrast {
        id: imageBrightness
        anchors.fill: imageBlur
        source: imageBlur
        brightness: -0.3
    }

    // UI elements
    Item {
        id: container

        anchors.fill: parent

        SearchField {
            id: searchField
            objectName: "searchField"

            width: 600
            height: 25

            anchors.centerIn: parent

            focus: true
            placeholder: "Type to search"

            completer: completer
        }

        Completer {
            id: completer
            objectName: "completer"

            width: searchField.width

            anchors.horizontalCenter: searchField.horizontalCenter
            anchors.top: searchField.bottom
            anchors.topMargin: 7

            model: actionsModel
        }

        Keys.forwardTo: searchField
    }
}
