import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

Node{
    property alias axisHelper: axisHelperInternal
    property color color: Qt.rgba(0.8, 0.2, 0.3, 1.0)

    AxisHelper {
        id: axisHelperInternal
        enableAxisLines: false
        enableXYGrid: false
        enableXZGrid: false
        enableYZGrid: false
    }
}
