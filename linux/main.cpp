#include <iostream>

#include <esUtil.h>

#include <linux_sound.h>
#include <linux_resource.h>
#include <framework/zframework.h>

int init( ESContext *esContext )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->init(esContext->width, esContext->height);
    return 1;
}

void draw( ESContext *esContext )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->update();
    framework->render();
}

void input( ESContext *esContext, int type, int x, int y )
{
    //std::cout << "x: " << x << " y: " << y << std::endl;
    zframework* framework = (zframework*) esContext->userData;
    switch (type) {
    case ButtonPressEvent:
        framework->input(touch_event::began, x, y);
        break;

    case ButtonReleaseEvent:
        framework->input(touch_event::end, x, y);
        break;

    case MotionNotifyEvent:
        framework->input(touch_event::move, x, y);
        break;
    }
}

int main( int argc, char *argv[] )
{
    linux_sound sound;
    linux_resource resource;
    zplatform platform(&sound, &resource);
    zframework framework(platform);

    ESContext esContext;

    esInitContext ( &esContext );
    esContext.userData = &framework;

    esCreateWindow ( &esContext, "ZeptoBird", 568, 320, ES_WINDOW_RGB | ES_WINDOW_DEPTH );

    if ( !init ( &esContext ) ) {
        return 1;
    }

    esRegisterDrawFunc ( &esContext, draw );
    esRegisterMouseFunc ( &esContext, input );

    esMainLoop ( &esContext );

    return 0;
}
