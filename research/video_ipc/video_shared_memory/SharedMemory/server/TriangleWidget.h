#ifndef TRIANGLEWIDGET_H
#define TRIANGLEWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QSharedMemory>
#include <QOffscreenSurface>
#include <QOpenGLFramebufferObject>

class TriangleWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    TriangleWidget(bool offscreen, QWidget *parent = nullptr);
    ~TriangleWidget();

protected:
    void initializeGL() override;
    void initializeOnscreen();
    void initializeOffscreen();
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void updateRotation();

private:
    void renderTriangleOnscreen();
    void renderTriangleOffscreen();
    void initOnscreenShaders();
     void initOffscreenShaders();
    void updateSharedMemory();

    QOpenGLShaderProgram *onscreen_program;
    QOpenGLShaderProgram *offscreen_program;
    QOpenGLBuffer onscreen_vbo;
    QOpenGLBuffer offscreen_vbo;
    QTimer *timer;
    QSharedMemory sharedMemory;
    QOffscreenSurface *offscreenSurface;
    QOpenGLContext *offscreenContext;
    QOpenGLFramebufferObject *offscreen_fbo;
    float angle;
    bool offscreen;

    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 color;

        out vec3 fragColor;

        uniform mat4 model;
        uniform mat4 projection;

        void main()
        {
            fragColor = color;
            gl_Position = projection * model * vec4(position, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 fragColor;
        out vec4 color;

        void main()
        {
            color = vec4(fragColor, 1.0);
        }
    )";
};

#endif // TRIANGLEWIDGET_H
