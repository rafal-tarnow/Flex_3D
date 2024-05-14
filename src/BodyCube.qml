import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

FBody{
    id: body
    property real xLenght: 100
    property real yLenght: 100
    property real zLenght: 100
    property bool xSymmetric: false

    Model{
        source: "#Cube"
        position: Qt.vector3d(xSymmetric === true ? 0 : parent.xLenght/2.0,parent.yLenght/2.0,parent.zLenght/2.0)
        scale: Qt.vector3d(parent.xLenght/100.0,parent.yLenght/100.0,parent.zLenght/100.0)
        materials: DefaultMaterial {
            diffuseColor: body.color
        }
    }
}
