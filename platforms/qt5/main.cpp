#include <QLabel>
#include <QApplication>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#   include "gles_view.h"
#endif

#include <qt5_sound.h>
#include <qt5_resource.h>
#include <framework/zframework.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube");
    app.setApplicationVersion("1.0");

#ifndef QT_NO_OPENGL
    qt5_sound sound;
    qt5_resource resource;

    zplatform platform(&sound, &resource);
    zframework framework(platform);

    GLESView view(&framework);
    view.setFixedSize(1024, 768);
    view.show();

#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    return app.exec();
}
