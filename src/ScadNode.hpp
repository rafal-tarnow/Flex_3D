#pragma once
#include <QtQuick3D/private/qquick3dnode_p.h>

class ScadNode: public QQuick3DNode{
    Q_OBJECT
    QML_NAMED_ELEMENT(ScadNode)
public:
    explicit ScadNode(QQuick3DNode * parent = nullptr);

};
