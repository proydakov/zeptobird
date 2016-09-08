#include <stdlib.h>
#include <iostream>

#include <esUtil.h>

#include <linux_resource.h>
#include <framework/zframework.h>

int init( ESContext *esContext )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->init(esContext->width, esContext->height);
}

void draw( ESContext *esContext )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->update();
    framework->render();
}

void input( ESContext *esContext, unsigned char, int, int )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->input();
}

int main( int argc, char *argv[] )
{
    linux_resource resource;
    zframework framework(&resource);

    ESContext esContext;

    esInitContext ( &esContext );
    esContext.userData = &framework;

    esCreateWindow ( &esContext, "ZeptoBird", 568, 320, ES_WINDOW_RGB | ES_WINDOW_DEPTH );

    if ( !init ( &esContext ) ) {
        return 1;
    }

    esRegisterDrawFunc ( &esContext, draw );
    esRegisterKeyFunc ( &esContext, input );

    esMainLoop ( &esContext );

    return 0;
}
