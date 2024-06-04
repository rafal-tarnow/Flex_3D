#pragma once

#include <QtQuick/private/qquickimage_p.h>

class ScadImage: public QQuickImage{
    Q_OBJECT
    QML_NAMED_ELEMENT(ScadImage)
public:
    ScadImage(QQuickItem *parent=0);
    ~ScadImage();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void touchEvent(QTouchEvent *event) override;
};
