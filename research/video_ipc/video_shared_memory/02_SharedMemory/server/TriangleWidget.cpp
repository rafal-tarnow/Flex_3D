#include "TriangleWidget.h"
#include <QMatrix4x4>
#include <QBuffer>
#include <QImage>
#include <QApplication>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLTexture>
#include <QElapsedTimer>
#include "../config.hpp"

TriangleWidget::TriangleWidget(bool offscreen, QWidget *parent)
    : QOpenGLWidget(parent), onscreen_angle(0.0f), onscreen_program(nullptr), sharedMemory("TriangleSharedMemory")
{
    // if (!sharedMemory.create(WIDTH * HEIGHT * 4)) {
    //     qDebug() << "Unable to create shared memory segment.";
    // }

    if (!sharedMemory.create(100000000)) {
        qDebug() << "Unable to create shared memory segment.";
    }
    qDebug() << "sharedMemory.size()" << sharedMemory.size();

    //QTimer::singleShot(0, [](){QApplication::quit();});

    resize(WIDTH,HEIGHT);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TriangleWidget::updateRotation);
    timer->start(16); // Około 60 FPS
}

TriangleWidget::~TriangleWidget()
{
    makeCurrent();
    onscreen_vbo.destroy();
    delete onscreen_program;
    doneCurrent();
    delete timer;
}

void TriangleWidget::initializeGL()
{
    initializeOpenGLFunctions();

    makeCurrent();
    initializeOnscreen();

    // //Offscreen surface
    // QSurfaceFormat format;
    // format.setDepthBufferSize(24);
    // offscreenSurface = new QOffscreenSurface();
    // offscreenSurface->setFormat(format);
    // offscreenSurface->create();

    // //opengl context
    // offscreenContext = new QOpenGLContext();
    // offscreenContext->setFormat(format);
    // offscreenContext->create();
    // offscreenContext->makeCurrent(offscreenSurface);

    // //framebuffer object
    // //makeCurrent();
    // QOpenGLFramebufferObjectFormat fboFormat;
    // fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    // offscreen_fbo = new QOpenGLFramebufferObject(width(), height(), fboFormat);
    // initializeOffscreen();
}

void TriangleWidget::initializeOnscreen()
{
    onscreen_program = new QOpenGLShaderProgram();
    onscreen_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    onscreen_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    onscreen_program->link();
    onscreen_program->bind();

    // Bufor wierzchołków
    GLfloat vertices[] = {
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    onscreen_vbo.create();
    onscreen_vbo.bind();
    onscreen_vbo.allocate(vertices, sizeof(vertices));

    // Atrybuty wierzchołków
    onscreen_program->enableAttributeArray(0);
    onscreen_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    onscreen_program->enableAttributeArray(1);
    onscreen_program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TriangleWidget::resizeGL(int w, int h)
{
    makeCurrent();
    glViewport(0, 0, w, h);
}

void TriangleWidget::paintGL()
{
    qDebug() << __FUNCTION__;
   // renderTriangleOnscreen();

    //makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 model;
    model.translate(0.0f, 0.0f, -5.0f);
    model.rotate(onscreen_angle, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);

    onscreen_program->bind();
    onscreen_program->setUniformValue("model", model);
    onscreen_program->setUniformValue("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 3);

}

void TriangleWidget::updateRotation()
{
    qDebug() << __FUNCTION__;
    onscreen_angle += 1.0f;
    if (onscreen_angle >= 360.0f) {
        onscreen_angle = 0.0f;
    }

    update();
    qDebug() << "post event";
    //renderTriangleOffscreen();
    updateSharedMemory();
}

void TriangleWidget::renderTriangleOnscreen()
{
    static int i = 0;
    qDebug() << __FUNCTION__ << " " << i++;


}

void TriangleWidget::updateSharedMemory()
{
    QElapsedTimer timer;
    timer.start();  // Rozpoczęcie pomiaru czasu


    //QImage image(offscreen_fbo->toImage());
    QImage image(this->grabFramebuffer());

    if (!sharedMemory.lock()) {
        qDebug() << "Unable to lock shared memory.";
        return;
    }

    char *to = static_cast<char*>(sharedMemory.data());
    const uchar *from = image.bits();
    qDebug() << "image.sizeInBytes() = " << image.sizeInBytes();
    qDebug() << image.format();
    qDebug() << "sharedMemory.size() = " << sharedMemory.size();
    memcpy(to, from, qMin(sharedMemory.size(), static_cast<int>(image.sizeInBytes())));

    sharedMemory.unlock();

    qDebug() << "Czas wykonania funkcji:" << timer.elapsed() << "ms";
}

// void TriangleWidget::updateSharedMemory()
// {

//     GLuint textureId = offscreen_fbo->texture();

//     if (textureId != 0) {

//         if (!sharedMemory.lock()) {
//             qDebug() << "Unable to lock shared memory.";
//             return;
//         }

//         QSize textureSize = offscreen_fbo->size();

//         int textureWidth = textureSize.width();
//         int textureHeight = textureSize.height();

//         glBindTexture(GL_TEXTURE_2D, textureId);
//         glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, sharedMemory.data());

//         sharedMemory.unlock();
//     } else {
//         qDebug() << "Failed to get texture from framebuffer object.";
//     }
// }

// void TriangleWidget::updateSharedMemory()
// {
//     offscreen_fbo->bind();
//     int w = offscreen_fbo->width();
//     int h = offscreen_fbo->height();
//     if (!sharedMemory.lock()) {
//         qDebug() << "Unable to lock shared memory.";
//         return;
//     }
//     char *to = static_cast<char*>(sharedMemory.data());
//     glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, to);
//     sharedMemory.unlock();
//     offscreen_fbo->release();
// }


