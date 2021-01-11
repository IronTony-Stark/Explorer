import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.2

import StyleSettings 1.0
import ResourceProvider 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    visibility: "Maximized"
    // width: 480
    // height: 640
    title: qsTr("Iron Explorer")

    BusyIndicatorImage {
        anchors.centerIn: parent
        width: Math.max(parent.width, parent.height) / 8
        height: width
        image: Resources.iconLoader
        running: busyIndicator.running
        z: 100
    }

    Dialog {
        id: errorDialog
        title: qsTr("Error Occured")
        width: 300
        height: 300

        contentItem: Rectangle {
            anchors.fill: parent

            Text {
                anchors.fill: parent
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
                text: errorText.error
                font.pointSize: 32
                color: Style.colorError
                wrapMode: Text.Wrap
            }
        }
    }

    Rectangle {
        id: header
        height: 70
        width: parent.width
        color: Style.colorHeader

        RowLayout {
            anchors.fill: parent

            Image {
                Layout.preferredHeight: 50
                Layout.preferredWidth: Layout.preferredHeight
                Layout.leftMargin: Style.marginSmall
                source: Resources.iconHome
                mipmap: true
                scale:  homeMouseArea.containsMouse ? 1.2 : 1.0

                MouseArea {
                    id: homeMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        fileList.addDestination(fileList.currentPath)
                        fileList.btnHomeClicked()
                    }
                }
            }

            Image {
                Layout.preferredHeight: 40
                Layout.preferredWidth: Layout.preferredHeight
                Layout.leftMargin: Style.marginSmall
                source: Resources.iconBack
                mipmap: true
                scale:  backMouseArea.containsMouse ? 1.2 : 1.0

                MouseArea {
                    id: backMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        fileList.btnBackClicked()
                    }
                }
            }

            Text {
                Layout.fillWidth: true
                Layout.leftMargin: 2 * Style.marginSmall
                text: fileList.currentPath
                color: Style.colorHeaderText
                font.pointSize: Style.headerTextSize
            }

            Switch {
                id: switchShowHidden
                Layout.alignment: Qt.AlignRight
                text: qsTr("Show Hidden")
                font.pointSize: Style.headerTextSize

                contentItem: Text {
                    text: switchShowHidden.text
                    font: switchShowHidden.font
                    color: Style.colorHeaderText
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: switchShowHidden.indicator.width + switchShowHidden.spacing
                }

                onCheckedChanged: {
                    fileList.setShowHidden(checked)
                }
            }
        }
    }

    FileTree {
        id: fileTree
        anchors {
            top: header.bottom
            left: parent.left
            bottom: parent.bottom
        }
        width: parent.width / 2

        model: fileTreeModel

        onExpanded: {
            fileTreeModel.expand(index)
        }

        onItemClicked: {
            fileList.addDestination(fileList.currentPath)
            fileTreeModel.changeDirectoryClicked(index)
        }
    }

    ListView {
        anchors {
            top: header.bottom
            left: fileTree.right
            right: parent.right
            bottom: parent.bottom
        }
        clip: true
        spacing: 5

        model: fileListModel

        delegate: Rectangle {

            function getIconSource() {
                if (isDirectory)
                    if (isReadable)
                        return Resources.iconDirectory
                    else
                        return Resources.iconLockedDirectory

                else
                    if (isReadable)
                        return Resources.iconFile
                    else
                        return Resources.iconLockedFile
            }

            width: ListView.view.width
            color: itemMouseArea.containsMouse ? Style.colorHighlight : Style.color
            height: 50

            RowLayout {
                anchors.fill: parent

                Image {
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: Layout.preferredHeight
                    Layout.leftMargin: Style.marginSmall
                    mipmap: true
                    source: getIconSource()
                }

                Text {
                    Layout.fillWidth: parent
                    text: name
                    color: itemMouseArea.containsMouse ? Style.colorTextHighlight : Style.colorText
                    font.pointSize: 12
                }
            }

            MouseArea {
                id: itemMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if (isDirectory && isReadable && name != "." && name != "..") {
                        fileList.addDestination(fileList.currentPath)
                        fileList.changeDirectoryClicked(name)
                    }
                }
            }
        }
    }

    Connections {
        target: errorText
        function onErrorChanged() {
            errorDialog.open()
        }
    }
}

