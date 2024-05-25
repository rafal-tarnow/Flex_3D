import QtQuick
import QtCore
import QtQuick3D
import QtQuick3D.Helpers

Node {

    AxisHelper {
        id: worldAxes
        enableXYGrid: false
        enableXZGrid: true
        enableYZGrid: false
    }

    Model {
        source: "#Cube"
        scale: Qt.vector3d(2.0, 2.0, 2.0)
        materials: DefaultMaterial {
            diffuseColor: Qt.rgba(0.0, 1.0, 0.0, 1.0)
        }
    }
}

BodySCAD{
    source: "componentTemplate.scad"
}
