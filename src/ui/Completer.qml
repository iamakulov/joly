import QtQuick 2.4
import QtQuick.Window 2.2

Rectangle {
    id: completer

    property alias count: listView.count
    property alias currentIndex: listView.currentIndex
    property alias currentItem: listView.currentItem
    property alias model: listView.model
    property int topMargin: Math.round(3 * 1.5)
    property int bottomMargin: Math.round(3 * 1.5)
    property int spacing: 0
    property int itemHeight: Math.round(32 * 1.5)

    signal launchAction(int actionId)

    function moveFocusUp() {
        if (currentIndex > 0)
            --currentIndex;
        else
            currentIndex = count - 1;
    }

    function moveFocusDown() {
        if (currentIndex < count - 1)
            ++currentIndex;
        else
            currentIndex = 0;
    }

    function launchActiveAction() {
        if (currentIndex !== -1) {
            completer.launchAction(completer.currentItem.actionId);
            userInterface.hide();
        }
    }

    border.width: 1
    border.color: "#ccc"
    color: "#fff"
    radius: 4 * 1.5

    ListView {
        id: listView

        anchors.fill: parent
        anchors.topMargin: completer.topMargin
        anchors.bottomMargin: completer.bottomMargin

        delegate: Rectangle {
            property int actionId: model.actionId

            height: completer.itemHeight
            width: completer.width
            color: "transparent"

            Image {
                id: delegateImage

                // model.actionId is an unique action identifier defined amd managed in action.h/.cpp.
                source: "image://ActionIcons/" + model.actionId

                height: 24 * 1.5
                width: 24 * 1.5

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4 * 1.5
            }

            Text {
                id: delegateText

                text: model.text
                font.pointSize: 16
                font.family: "Segoe UI"
                color: "#333"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: delegateImage.right
                anchors.leftMargin: 4 * 1.5
            }
        }

        highlight: Rectangle {
            width: completer.width
            height: completer.itemHeight
            color: "#10000000"
            y: (listView.currentItem) ? listView.currentItem.y : 0;
        }

        /* #highlightFollowsCurrentItem is disabled because we implement
         * a SmoothedAnimation in #highlight property
         * with slightly different characteristics: with constant duration instead of velocity.
         * Moreover, this implementing is also better that the default one
         * because it animates currentItem changes made with mouse. */
        highlightFollowsCurrentItem: false

        spacing: completer.spacing
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            completer.launchActiveAction();
        }

        onPositionChanged: {
            var indexAt = listView.indexAt(mouse.x, mouse.y);
            // We want to save the item focused when the mouse leaves it out of Completer.
            if (indexAt !== -1)
                completer.currentIndex = indexAt;
        }
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
