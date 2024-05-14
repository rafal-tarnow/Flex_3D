import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: defaultMaterial_material
        objectName: "DefaultMaterial"
        baseColor: "#ff999999"
        indexOfRefraction: 1
    }

    // Nodes:
    Node {
        id: profile_8080_obj
        objectName: "profile_8080.obj"
        Model {
            id: defaultobject
            objectName: "defaultobject"
            source: "defaultobject_mesh.mesh"
            materials: [defaultMaterial_material]
        }
    }

    // Animations:
}
