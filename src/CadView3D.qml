import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls

View3D {
    id: root

    //OpenScad
    // property var homeCameraPosition: Qt.vector3d(1193, -3885, 1280)
    // property var homeCameraRotation: Qt.quaternion(0.777, 0.628, -0.012, 0.011)

    //Qt
    property var homeCameraPosition: Qt.vector3d(1193, 1005, 1000)
    property var homeCameraRotation: Qt.quaternion(0.879, -0.266, 0.377, 0.1145)

    property alias partSource: loaderNode.source

    environment: SceneEnvironment {
        clearColor: "#FFFFFF"
        backgroundMode: SceneEnvironment.Color
        antialiasingMode: SceneEnvironment.MSAA
        antialiasingQuality: SceneEnvironment.High
    }

    camera: cameraPerspective

    property var bck: backend

    importScene: Node {

        Loader3D {
            id: loaderNode

            onLoaded: {
                //we use try catch because not all loaded scenes have gui property
                try {
                    item.gui.parent = root
                } catch (error) {
                    console.log(error)
                }
            }

            //property var userNode: null
            PerspectiveCamera {
                id: cameraPerspective
                z: 600
                // position: homeCameraPosition
                // rotation: homeCameraRotation
            }
        }
    }

    Item {
        z: 2
        anchors.right: parent.right
        anchors.top: parent.top

        Text {
            id: camPositionTxt
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("Camera position: " + root.camera.position.toString())
        }

        Text {
            id: camRotationTxt
            anchors.right: parent.right
            anchors.top: camPositionTxt.bottom
            text: qsTr("Camera rotation: " + root.camera.rotation.toString())
        }

        Button {
            id: homeCamPositionButton
            anchors.right: parent.right
            anchors.top: camRotationTxt.bottom
            text: qsTr("Home Camera")

            onClicked: {
                cameraPerspective.position = homeCameraPosition
                cameraPerspective.rotation = homeCameraRotation
            }
        }
    }

    // OriginGizmo {
    //     id: originGizmo
    //     anchors.top: homeCamPosition.bottom
    //     anchors.right: parent.right
    //     anchors.margins: 10
    //     width: 120
    //     height: 120
    //     targetNode: embedNode

    //     // onAxisClicked: axis => {
    //     //                    arcballController.jumpToAxis(axis)
    //     //                }
    // }
    DebugView {
        z: 2
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: root
        resourceDetailsVisible: false
    }

    OrbitCameraController {
        //anchors.fill: parent
        origin: loaderNode
        camera: cameraPerspective
    }
    // WasdController {
    //     controlledObject: cameraPerspective
    // }
    DirectionalLight {
        eulerRotation: Qt.vector3d(-135, -110, 0)
        brightness: 1
    }

    SpotLight {
        position: Qt.vector3d(0, 500, 600)
        eulerRotation.x: -45
        brightness: 30
    }
}
