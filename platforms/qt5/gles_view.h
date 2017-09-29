#pragma once

#include <QBasicTimer>
#include <QOpenGLWidget>

class zframework;

class GLESView : public QOpenGLWidget
{
public:
    GLESView(zframework* framework, QWidget *parent = 0);
    virtual ~GLESView();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    zframework* framework_;
    QBasicTimer timer_;
};
