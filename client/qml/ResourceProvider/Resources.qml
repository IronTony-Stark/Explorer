pragma Singleton

import QtQuick 2.0

QtObject {
    readonly property string path: "qrc:/qml/ResourceProvider/resources/"

    readonly property string iconLoader: path + "loader.svg"

    readonly property string iconHome: path + "home.svg"
    readonly property string iconBack: path + "arrow_left.svg"

    readonly property string iconRight: path + "arrow_right.svg"
    readonly property string iconDown: path + "arrow_down.svg"

    readonly property string iconDirectory: path + "directory.png"
    readonly property string iconFile: path + "fs_file.png"
    readonly property string iconLockedDirectory: path + "locked_directory.png"
    readonly property string iconLockedFile: path + "locked_file.png"
}
