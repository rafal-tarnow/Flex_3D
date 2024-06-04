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
    qDebug() << __PRETTY_FUNCTION__;
    ScadControllerServer::getInstance(this)->sendMouseDoubleClickEvent(event);
}

void ScadImage::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    ScadControllerServer::getInstance(this)->sendMouseMoveEvent(event);
}

void ScadImage::mousePressEvent(QMouseEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    //QQuickImage::mousePressEvent(event);
    ScadControllerServer::getInstance(this)->sendMousePressEvent(event);
}

void ScadImage::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    ScadControllerServer::getInstance(this)->sendMouseReleaseEvent(event);
}

void ScadImage::wheelEvent(QWheelEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    ScadControllerServer::getInstance(this)->sendWheelEvent(event);
}

void ScadImage::touchEvent(QTouchEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    //QQuickImage::touchEvent(event);
}
