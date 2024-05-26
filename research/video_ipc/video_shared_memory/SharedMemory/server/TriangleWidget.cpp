#include "TriangleWidget.h"
#include <QMatrix4x4>
#include <QBuffer>
#include <QImage>
#include <QApplication>
#include <QOpenGLFramebufferObjectFormat>

TriangleWidget::TriangleWidget(bool offscreen, QWidget *parent)
    : QOpenGLWidget(parent), angle(0.0f), onscreen_program(nullptr),offscreen_program(nullptr), sharedMemory("TriangleSharedMemory"),
    offscreen(offscreen), offscreen_fbo(nullptr)
{
    if (!sharedMemory.create(1700 * 900 * 4)) {
        qDebug() << "Unable to create shared memory segment.";
    }
    resize(1700,900);


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
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    offscreen_vbo.create();
    offscreen_vbo.bind();
    offscreen_vbo.allocate(vertices, sizeof(vertices));

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
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    update();
    qDebug() << "post event";
    //renderTriangleOffscreen();
}

void TriangleWidget::renderTriangleOnscreen()
{
    static int i = 0;
    qDebug() << __FUNCTION__ << " " << i++;

    makeCurrent();
    if (offscreen) {
        offscreen_fbo->bind();
    }


    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 model;
    model.translate(0.0f, 0.0f, -5.0f);
    model.rotate(angle, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);

    onscreen_program->bind();
    onscreen_program->setUniformValue("model", model);
    onscreen_program->setUniformValue("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 3);




}

void TriangleWidget::renderTriangleOffscreen()
{
    offscreenContext->makeCurrent(offscreenSurface);

    offscreen_fbo->bind();

    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 model;
    model.translate(0.0f, 0.0f, -5.0f);
    model.rotate(angle, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);

    offscreen_program->bind();
    offscreen_program->setUniformValue("model", model);
    offscreen_program->setUniformValue("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // updateSharedMemory();

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
