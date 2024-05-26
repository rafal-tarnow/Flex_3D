#include "TriangleWidget.h"
#include <QMatrix4x4>
#include <QBuffer>
#include <QImage>
#include <QApplication>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLTexture>
#include "../config.hpp"

TriangleWidget::TriangleWidget(bool offscreen, QWidget *parent)
    : QOpenGLWidget(parent), onscreen_angle(0.0f), offscreen_angle(0.0f), onscreen_program(nullptr),offscreen_program(nullptr), sharedMemory("TriangleSharedMemory"),
    offscreen(offscreen), offscreen_fbo(nullptr)
{
    if (!sharedMemory.create(WIDTH * HEIGHT * 4)) {
        qDebug() << "Unable to create shared memory segment.";
        QApplication::quit();
    }
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


    delete offscreen_fbo;
    delete offscreenSurface;
    delete offscreenContext;

}

void TriangleWidget::initializeGL()
{
    initializeOpenGLFunctions();

    makeCurrent();
    initializeOnscreen();

    //Offscreen surface
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    offscreenSurface = new QOffscreenSurface();
    offscreenSurface->setFormat(format);
    offscreenSurface->create();

    //opengl context
    offscreenContext = new QOpenGLContext();
    offscreenContext->setFormat(format);
    offscreenContext->create();
    offscreenContext->makeCurrent(offscreenSurface);

    //framebuffer object
    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    offscreen_fbo = new QOpenGLFramebufferObject(width(), height(), fboFormat);
    initializeOffscreen();
}

void TriangleWidget::initializeOnscreen()
{
    // Inicjalizacja shaderów
    initOnscreenShaders();

    // Bufor wierzchołków
    GLfloat vertices[] = {
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f
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

void TriangleWidget::initializeOffscreen()
{
    // Inicjalizacja shaderów
    initOffscreenShaders();

    // Bufor wierzchołków
    GLfloat vertices[] = {
        // Pozycje            // Kolory
        -1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    offscreen_vbo.create();
    offscreen_vbo.bind();
    offscreen_vbo.allocate(vertices, sizeof(vertices));

    // Element Buffer Object (EBO) dla kwadratu
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atrybuty wierzchołków
    offscreen_program->enableAttributeArray(0);
    offscreen_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    offscreen_program->enableAttributeArray(1);
    offscreen_program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TriangleWidget::initOnscreenShaders()
{
    onscreen_program = new QOpenGLShaderProgram();
    onscreen_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    onscreen_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    onscreen_program->link();
    onscreen_program->bind();
}

void TriangleWidget::initOffscreenShaders()
{
    offscreen_program = new QOpenGLShaderProgram();
    offscreen_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    offscreen_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    offscreen_program->link();
    offscreen_program->bind();
}

void TriangleWidget::resizeGL(int w, int h)
{
    makeCurrent();
    glViewport(0, 0, w, h);

    offscreenContext->makeCurrent(offscreenSurface);
    delete offscreen_fbo;
    //framebuffer object
    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    offscreen_fbo = new QOpenGLFramebufferObject(width(), height(), fboFormat);
}

void TriangleWidget::paintGL()
{
    qDebug() << __FUNCTION__;
    renderTriangleOnscreen();
}

void TriangleWidget::updateRotation()
{
    qDebug() << __FUNCTION__;
    onscreen_angle += 1.0f;
    if (onscreen_angle >= 360.0f) {
        onscreen_angle = 0.0f;
    }

    offscreen_angle += 1.0f;
    if (offscreen_angle >= 360.0f) {
        offscreen_angle = 0.0f;
    }

    update();
    qDebug() << "post event";
    renderTriangleOffscreen();
    updateSharedMemory();
}

void TriangleWidget::renderTriangleOnscreen()
{
    static int i = 0;
    qDebug() << __FUNCTION__ << " " << i++;

    makeCurrent();

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

void TriangleWidget::renderTriangleOffscreen()
{
    qDebug() << __FUNCTION__;
    offscreenContext->makeCurrent(offscreenSurface);
    offscreen_fbo->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 model;
    model.translate(0.0f, 0.0f, -5.0f);
    model.rotate(offscreen_angle, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);

    offscreen_program->bind();
    offscreen_program->setUniformValue("model", model);
    offscreen_program->setUniformValue("projection", projection);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    offscreen_fbo->release();
}

void TriangleWidget::updateSharedMemory()
{
    QImage image(offscreen_fbo->toImage());

    if (!sharedMemory.lock()) {
        qDebug() << "Unable to lock shared memory.";
        return;
    }

    char *to = static_cast<char*>(sharedMemory.data());
    const uchar *from = image.bits();
    memcpy(to, from, qMin(sharedMemory.size(), static_cast<int>(image.sizeInBytes())));

    sharedMemory.unlock();
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

//         // Rozmiary tekstury
//         int textureWidth = textureSize.width();
//         int textureHeight = textureSize.height();

//         // Odczytaj dane tekstury bezpośrednio do pamięci współdzielonej
//         glBindTexture(GL_TEXTURE_2D, textureId);
//         glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, sharedMemory.data());

//         // Zwolnij pamięć współdzieloną
//         sharedMemory.unlock();
//     } else {
//         qDebug() << "Failed to get texture from framebuffer object.";
//     }
// }

// void TriangleWidget::updateSharedMemory()
// {
//     // Upewnij się, że framebuffer jest bindowany
//     offscreen_fbo->bind();

//     // Rozmiary okna
//     int w = offscreen_fbo->width();
//     int h = offscreen_fbo->height();

//     // Upewnij się, że pamięć współdzielona jest zablokowana przed zapisem
//     if (!sharedMemory.lock()) {
//         qDebug() << "Unable to lock shared memory.";
//         return;
//     }

//     // Pobierz wskaźnik do danych pamięci współdzielonej
//     char *to = static_cast<char*>(sharedMemory.data());

//     // Odczytaj piksele z FBO do pamięci współdzielonej
//     glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, to);

//     // Zwolnij pamięć współdzieloną
//     sharedMemory.unlock();

//     // Odwiąż framebuffer
//     offscreen_fbo->release();
// }


