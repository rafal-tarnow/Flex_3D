import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls

View3D {
    id: root

    Item {
        z: 2
        anchors.right: parent.right
        anchors.top: parent.top

        Button {
            id: homeCamPosition
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("Reset Camera")
            onClicked: {
                cameraPerspective.position = Qt.vector3d(-1200, 750, 700)
                cameraPerspective.rotation = Qt.quaternion(0.87, -0.22,
                                                           -0.42, -0.1)
            }
        }

        DebugView {
            anchors.right: parent.right
            anchors.top: homeCamPosition.bottom
            source: root
            resourceDetailsVisible: false
        }
    }

    environment: SceneEnvironment {
        clearColor: "#FFFFFF"
        backgroundMode: SceneEnvironment.Color
        antialiasingMode: SceneEnvironment.MSAA
        antialiasingQuality: SceneEnvironment.High
    }

    camera: cameraPerspective

    PerspectiveCamera {
        id: cameraPerspective
        property real cameraAnimation: 1
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
        position: Qt.vector3d(-1200, 750, 700)
        rotation: Qt.quaternion(0.87, -0.22, -0.42, -0.1)
    }

    // OrbitCameraController {
    //     anchors.fill: parent
    //     // origin: originNode
    //     // camera: cameraPerspective
    //     origin: cameraPerspective
    //     camera: originNode
    // }
    WasdController {
        controlledObject: cameraPerspective
    }

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
