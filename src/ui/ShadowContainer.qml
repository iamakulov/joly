import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    id: shadowContainer

    property int shadowSize: 24 * 1.5
    property var innerElement: shadowContainer.children[1]

    anchors.margins: shadowContainer.shadowSize

    DropShadow {
        anchors.fill: innerElement
        horizontalOffset: 0
        verticalOffset: 2 * 1.5
        radius: shadowContainer.shadowSize
        samples: shadowContainer.shadowSize * 2
        color: "#30000000"
        source: innerElement
    }

    Component.onCompleted: {
        console.assert(shadowContainer.children.length === 2)   // DropShadow + innerElement
    }
}
