import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls

Item {

    Column {
        z: 2
        anchors.right: parent.right
        anchors.top: parent.top
        spacing: 2

        Button {
            id: homeCamPosition
            width: 50
            onClicked: {
                cameraPerspective.position = Qt.vector3d(-1200, 750, 700)
                cameraPerspective.rotation = Qt.quaternion(0.87, -0.22,
                                                           -0.42, -0.1)
            }
        }

        Slider {
            id: cuttingAreaXSizeSlider
            width: 200
            from: 200
            to: 2000
            value: 700
        }

        Text {
            id: dbgText1
            text: cameraPerspective.position.toString()
        }

        Text {
            id: dbgText2
            text: cameraPerspective.rotation.toString()
        }

        DebugView {
            source: v3d
            resourceDetailsVisible: false
        }
    }

    View3D {
        id: v3d
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "#FFFFFF"
            backgroundMode: SceneEnvironment.Color
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        camera: cameraPerspective

        Text {
            x: 0
            y: 0
            width: 400
            height: 400
            id: dbgTxt1
            text: qsTr("text")
        }

        Node {
            id: originNode

            AxisHelper {
                id: worldAxes
                // enableXYGrid: true
                // enableXZGrid: false
                // enableYZGrid: false
            }

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

        OrbitCameraController {
            anchors.fill: parent
            // origin: originNode
            // camera: cameraPerspective
            origin: cameraPerspective
            camera: originNode
        }

        // WasdController {
        //     controlledObject: cameraPerspective
        // }
        property color aluminiumColor: Qt.rgba(0.3, 0.3, 0.3, 1.0)

        BodyCube {
            id: cuttingArea
            position: Qt.vector3d(0, 0, 0)
            xLenght: cuttingAreaXSizeSlider.value
            yLenght: 100
            zLenght: 800
            xSymmetric: true
            color: Qt.rgba(0.7, 0.6, 0.1, 1.0)
        }

        // Node {
        //     id: base
        //     property real baseWidth: cuttingArea.xLenght + 2 * 80
        //     property bool helperAxis: false
        //     property color color: Qt.rgba(0.4, 0.4, 0.4, 1.0)

        //     BodyCube {
        //         position: Qt.vector3d(0, -80, 0)
        //         xLenght: parent.baseWidth
        //         yLenght: 80
        //         zLenght: 80
        //         xSymmetric: true
        //         axisHelper.enableAxisLines: base.helperAxis
        //         color: base.color
        //     }

        //     BodyCube {
        //         position: Qt.vector3d(0, -80, 200)
        //         xLenght: parent.baseWidth
        //         yLenght: 80
        //         zLenght: 80
        //         xSymmetric: true
        //         axisHelper.enableAxisLines: base.helperAxis
        //         color: base.color
        //     }

        //     BodyCube {
        //         position: Qt.vector3d(0, -80, 400)
        //         xLenght: parent.baseWidth
        //         yLenght: 80
        //         zLenght: 80
        //         xSymmetric: true
        //         axisHelper.enableAxisLines: base.helperAxis
        //         color: base.color
        //     }
        // }
        Node {
            id: supports
            position: Qt.vector3d(0, 80, 0)
            visible: true
            BodyCube {
                id: leftSupport
                position: Qt.vector3d(
                              cuttingArea.xLenght / 2 + xLenght / 2 + 10, 0, 0)
                xLenght: 80
                yLenght: 80
                zLenght: cuttingArea.zLenght
                xSymmetric: true
                color: aluminiumColor
                axisHelper.enableAxisLines: true
            }

            BodyCube {
                id: rightSupport
                position: Qt.vector3d(
                              -(cuttingArea.xLenght / 2 + xLenght / 2 + 10), 0,
                              0)
                xLenght: 80
                yLenght: 80
                zLenght: cuttingArea.zLenght
                xSymmetric: true
                color: aluminiumColor
                axisHelper.enableAxisLines: true
            }
        }

        Model {
            source: "#Rectangle"
            y: -500
            scale: Qt.vector3d(12, 12, 12)
            eulerRotation.x: -90
            materials: DefaultMaterial {
                diffuseColor: Qt.rgba(0.5, 0.5, 0.5, 1.0)
                cullMode: Material.NoCulling
            }
        }
        Model {
            source: "#Rectangle"
            x: -600
            scale: Qt.vector3d(12, 10, 12)
            eulerRotation.y: 90
            materials: DefaultMaterial {
                diffuseColor: Qt.rgba(0.8, 0.8, 0.6, 1.0)
                cullMode: Material.NoCulling
            }
        }
        Model {
            source: "#Rectangle"
            z: -600
            scale: Qt.vector3d(12, 10, 12)
            materials: DefaultMaterial {
                diffuseColor: Qt.rgba(0.8, 0.8, 0.6, 1.0)
                cullMode: Material.NoCulling
            }
        }

        Node {
            position: Qt.vector3d(0, 100, -120)
            // AxisHelper{
            //     enableAxisLines: true
            //     enableXYGrid: true
            //     enableXZGrid: false
            //     enableYZGrid: false
            // }
            Item {
                width: 400
                height: 400
                anchors.centerIn: parent
                Rectangle {
                    anchors.fill: parent
                    opacity: 0.4
                    color: "#202020"
                    radius: 10
                    border.width: 2
                    border.color: "#f0f0f0"
                }
            }
        }

        Node {
            position: Qt.vector3d(0, 150, 100)

            NumberAnimation on eulerRotation.z {
                loops: Animation.Infinite
                from: 0
                to: 360
                duration: 4000
                easing.type: Easing.InOutBack
            }
            Item {
                width: 400
                height: 400
                anchors.centerIn: parent
                // This allows rendering into offscreen surface and caching it.
                layer.enabled: true
                Rectangle {
                    x: 150
                    y: 100
                    width: 100
                    height: 100
                    radius: 50
                    color: "#80808020"
                    border.color: "black"
                    border.width: 2
                }
                Rectangle {
                    x: 90
                    y: 200
                    width: 100
                    height: 100
                    radius: 50
                    color: "#80808020"
                    border.color: "black"
                    border.width: 2
                }
                Rectangle {
                    x: 210
                    y: 200
                    width: 100
                    height: 100
                    radius: 50
                    color: "#80808020"
                    border.color: "black"
                    border.width: 2
                }
            }
        }

        //! [circles item]
        Node {
            position: Qt.vector3d(0, 800, 0)

            Model {
                source: "#Cylinder"
                y: -300
                scale: Qt.vector3d(0.1, 6.1, 0.1)
                materials: DefaultMaterial {
                    diffuseColor: Qt.rgba(0.9, 0.9, 0.9, 1.0)
                }
            }
            Model {
                source: "#Sphere"
                y: -700
                scale: Qt.vector3d(2, 2, 2)
                materials: DefaultMaterial {
                    diffuseColor: Qt.rgba(0.4, 0.4, 0.4, 1.0)
                }
            }
        }
    }
}
