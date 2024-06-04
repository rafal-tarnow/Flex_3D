#include "ScadImage.hpp"
#include "ScadControllerServer.hpp"

ScadImage::ScadImage(QQuickItem *parent)
    : QQuickImage(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
}

ScadImage::~ScadImage()
{
}

void ScadImage::mouseDoubleClickEvent(QMouseEvent *event)
{
    ScadControllerServer::getInstance(this)->sendMouseDoubleClickEvent(event);
}

void ScadImage::mouseMoveEvent(QMouseEvent *event)
{
    ScadControllerServer::getInstance(this)->sendMouseMoveEvent(event);
}

void ScadImage::mousePressEvent(QMouseEvent *event)
{
    //QQuickImage::mousePressEvent(event);
    ScadControllerServer::getInstance(this)->sendMousePressEvent(event);
}

void ScadImage::mouseReleaseEvent(QMouseEvent *event)
{
    ScadControllerServer::getInstance(this)->sendMouseReleaseEvent(event);
}

void ScadImage::wheelEvent(QWheelEvent *event)
{
    ScadControllerServer::getInstance(this)->sendWheelEvent(event);
}

void ScadImage::touchEvent(QTouchEvent *event)
{
    //QQuickImage::touchEvent(event);
}
