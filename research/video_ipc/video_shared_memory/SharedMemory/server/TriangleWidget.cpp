#include "TriangleWidget.h"
#include <QMatrix4x4>
#include <QBuffer>
#include <QImage>

TriangleWidget::TriangleWidget(QWidget *parent)
    : QOpenGLWidget(parent), angle(0.0f), program(nullptr), sharedMemory("TriangleSharedMemory")
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
    vbo.destroy();
    delete program;
    doneCurrent();
    delete timer;
}

void TriangleWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Inicjalizacja shaderów
    initShaders();

    // Bufor wierzchołków
    GLfloat vertices[] = {
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    // Atrybuty wierzchołków
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TriangleWidget::initShaders()
{
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();
    program->bind();
}

void TriangleWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TriangleWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 model;
    model.translate(0.0f, 0.0f, -5.0f);
    model.rotate(angle, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 projection;
    projection.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);

    program->bind();
    program->setUniformValue("model", model);
    program->setUniformValue("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Aktualizacja stanu wyrenderowanego obrazu w pamięci współdzielonej
    updateSharedMemory();
}

void TriangleWidget::updateRotation()
{
    angle += 1.0f;
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    update();
}

void TriangleWidget::updateSharedMemory()
{
    QImage image(size(), QImage::Format_RGBA8888);
    glReadPixels(0, 0, width(), height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    image = image.mirrored();

    if (!sharedMemory.lock()) {
        qDebug() << "Unable to lock shared memory.";
        return;
    }

    char *to = static_cast<char*>(sharedMemory.data());
    const uchar *from = image.bits();
    memcpy(to, from, qMin(sharedMemory.size(), static_cast<int>(image.sizeInBytes())));

    sharedMemory.unlock();
}
