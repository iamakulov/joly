import QtQuick 2.0

Rectangle {
    id: completer

    property alias count: listView.count
    property alias currentIndex: listView.currentIndex
    property alias currentItem: listView.currentItem
    property alias model: listView.model
    property int topMargin: 3
    property int bottomMargin: 3
    property int spacing: 0
    property int itemHeight: 24

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

    color: Qt.rgba(0, 0, 0, 0.6)
    height: topMargin + count * itemHeight + (count - 1) * spacing + bottomMargin
    radius: 3

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

                height: 16
                width: 16

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4
            }

            Text {
                id: delegateText

                text: model.text
                color: "#ececec"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: delegateImage.right
                anchors.leftMargin: 4
            }
        }

        highlight: Rectangle {
            width: completer.width
            height: completer.itemHeight
            color: Qt.rgba(255, 255, 255, 0.2)
            y: (listView.currentItem) ? listView.currentItem.y : 0;

            Behavior on y {
                SmoothedAnimation {
                    duration: 250
                }
            }
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

    states: [
        State {
            name: "hidden"
            when: model.count === 0

            PropertyChanges {
                target: completer
                visible: false
            }
        }
    ]
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
