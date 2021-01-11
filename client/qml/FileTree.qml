import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import StyleSettings 1.0
import ResourceProvider 1.0

TreeView {
    id: tree
    signal itemClicked(var index)
    headerVisible: false
    frameVisible: false
    style: TreeViewStyle {
        indentation: 20

        branchDelegate: Image {

            function getIcon() {
                if (!styleData.hasChildren)
                    return ""

                return styleData.isExpanded ? Resources.iconDown : Resources.iconRight
            }

            width: indentation
            height: indentation
            anchors.leftMargin: Style.marginSmall
            source: getIcon()
        }

        itemDelegate: Rectangle {

            color: itemMouseArea.containsMouse ? Style.colorHighlight : Style.color

            Image {
                id: icon
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: Style.marginSmall
                width: 30
                height: width
                source: Resources.iconDirectory
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: icon.right
                anchors.leftMargin: Style.marginSmall
                text: styleData.value
                color: itemMouseArea.containsMouse ? Style.colorTextHighlight : Style.colorText
                font.pointSize: 12
            }

            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    tree.itemClicked(styleData.index);
                }
            }
        }

        rowDelegate: Rectangle {
            id: rowDelegate
            height: 30
        }
    }

    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    TableViewColumn {
        role: "display"
        title: "File System"
    }
}
