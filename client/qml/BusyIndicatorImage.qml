import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

BusyIndicator {
    property string image
    property int speed: 2000

    style: BusyIndicatorStyle {
        indicator: Image {
            visible: control.running
            source: image
            mipmap: true
            RotationAnimator on rotation {
                running: control.running
                loops: Animation.Infinite
                duration: speed
                from: 0 ; to: 360
            }
        }
    }
}
