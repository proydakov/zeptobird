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

void input( ESContext *esContext, int x, int y )
{
    std::cout << "x: " << x << " y: " << y << std::endl;
    zframework* framework = (zframework*) esContext->userData;
    framework->input();
}

int main( int argc, char *argv[] )
{
    linux_sound sound;
    linux_resource resource;
    zframework framework(&resource, &sound);

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
