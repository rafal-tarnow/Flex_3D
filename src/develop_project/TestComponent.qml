import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import QtQuick3D.AssetUtils
import Flex3D
import "."


Node {
	id: v3d


	property var gui : Item {
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
			Text{
				text: "Base offset: " + baseOffset.value
			}
			Slider {
				id: baseOffset
				from: 20
				to: 1000
				value: 200
			}
		}
	}




	property color aluminiumColor: Qt.rgba(0.3, 0.3, 0.3, 1.0)

	Node {
		id: originNode

		AxisHelper {
			id: worldAxes
			enableXYGrid: false
			enableXZGrid: true
			enableYZGrid: false
		}
	}

	// Model {
	// 	source: "#Sphere"
	// 	scale: Qt.vector3d(2.0, 2.0, 2.0)
	// 	materials: DefaultMaterial {
	// 		diffuseColor: Qt.rgba(0.0, 1.0, 0.1, 1.0)
	// 	}
	// }


	// BodyCube {
	// 	position: Qt.vector3d(0, 0, 0)
	// 	xLenght: 100
	// 	yLenght: 100
	// 	zLenght: 800
	// 	xSymmetric: false
	// 	color: Qt.rgba(0.7, 0.6, 0.1, 1.0)
	// }

	// RuntimeLoader {
	// 	id: importNode
	// 	source: "file:///C:/Users/rafal/Documents/Flex_3D/src/develop_project/profile_8080.obj"
	// 	//source: "file:///profile_2020.obj"
	// }

	// Body8080{

	// }


	//base
	Node {
		id: base


		Loader3D {
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(200, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(400, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(600, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(800, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1000, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1200, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1400, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1600, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1800, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2000, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2200, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2400, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2600, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

	}

	//base -200
	Node {
		id: base2
		position: Qt.vector3d(0, -baseOffset.value, 0)


		Loader3D {
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(200, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(400, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(600, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(800, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1000, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1200, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1400, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1600, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(1800, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2000, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2200, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2400, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

		Loader3D {
			position: Qt.vector3d(2600, 0, 0)
			eulerRotation.x: 90
			source: "file:///" + SOURCE_DIR + "/develop_project/balsamui/Profile_8080.qml"
			asynchronous: true
			visible: status == Loader3D.Ready
		}

	}



}

/*
import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import Flex3D


Node {
	id: v3d



	property color aluminiumColor: Qt.rgba(0.3, 0.3, 0.3, 1.0)

	Node {
		id: originNode

		AxisHelper {
			id: worldAxes
			// enableXYGrid: true
			// enableXZGrid: false
			// enableYZGrid: false
		}


		BodyCube {
			id: cuttingArea
			position: Qt.vector3d(0, 0, 0)
			xLenght: cuttingAreaXSizeSlider.value
			yLenght: 100
			zLenght: 800
			xSymmetric: true
			color: Qt.rgba(0.7, 0.6, 0.1, 1.0)
		}

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
*/