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

    importScene: Node {
        id: embedNode
        property var userNode: null

        PerspectiveCamera {
            id: cameraPerspective
            z: 600

            // property real cameraAnimation: 1
            // SequentialAnimation {
            //     loops: Animation.Infinite
            //     running: true
            //     NumberAnimation {
            //         target: camera
            //         property: "cameraAnimation"
            //         to: -1
            //         duration: 5000
            //         easing.type: Easing.InOutQuad
            //     }
            //     NumberAnimation {
            //         target: camera
            //         property: "cameraAnimation"
            //         to: 1
            //         duration: 5000
            //         easing.type: Easing.InOutQuad
            //     }
            // }
            // position: homeCameraPosition
            // rotation: homeCameraRotation
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
            text: qsTr("Camera position: " + embedNode.position.toString())
        }

        Text {
            id: camRotationTxt
            anchors.right: parent.right
            anchors.top: camPositionTxt.bottom
            text: qsTr("Camera rotation: " + embedNode.rotation.toString())
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

    environment: SceneEnvironment {
        clearColor: "#FFFFFF"
        backgroundMode: SceneEnvironment.Color
        antialiasingMode: SceneEnvironment.MSAA
        antialiasingQuality: SceneEnvironment.High
    }

    camera: cameraPerspective

    OrbitCameraController {
        //anchors.fill: parent
        origin: embedNode
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
