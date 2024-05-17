import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import QtQuick3D
import QtQuick3D.Helpers

Node {

    property var gui: Item {
        x: 10
        y: 10
        Column {
            spacing: 5
            Button {
                text: "OK"
            }
            Button {
                text: "YES"
            }
            Slider {}
            Slider {}
            Slider {}
            Slider {}
        }
    }

    AxisHelper {
        id: worldAxes
        enableXYGrid: false
        enableXZGrid: true
        enableYZGrid: false
    }

    Model {
        source: "#Sphere"
        scale: Qt.vector3d(2.0, 2.0, 2.0)
        materials: DefaultMaterial {
            diffuseColor: Qt.rgba(0.0, 1.0, 0.0, 1.0)
        }
    }
}
