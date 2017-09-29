#include "gles_view.h"

#include <QMouseEvent>

#include <framework/zframework.h>

GLESView::GLESView(zframework* framework, QWidget *parent) :
    QOpenGLWidget(parent),
    framework_(framework)
{
}

GLESView::~GLESView()
{
    makeCurrent();

    framework_->deinit();

    doneCurrent();
}

void GLESView::mousePressEvent(QMouseEvent *e)
{
    framework_->input(touch_event::began, e->x(), e->y());
}

void GLESView::mouseReleaseEvent(QMouseEvent *e)
{
    framework_->input(touch_event::end, e->x(), e->y());
}

void GLESView::mouseMoveEvent(QMouseEvent *e)
{
    framework_->input(touch_event::move, e->x(), e->y());
}

void GLESView::timerEvent(QTimerEvent *)
{
    framework_->update();
    update();
}

void GLESView::initializeGL()
{
    // init gl
    framework_->init(width(), height());

    // Use QBasicTimer because its faster than QTimer
    timer_.start(12, this);
}

void GLESView::resizeGL(int w, int h)
{

}

void GLESView::paintGL()
{
    framework_->render();
}
