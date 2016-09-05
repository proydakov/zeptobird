#include <stdlib.h>
#include <iostream>

#include <esUtil.h>

#include <linux_resource.h>
#include <framework/zframework.h>

///
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->init(esContext->width, esContext->height);
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->update();
    framework->render();
}

///
// Input key
//
void Input ( ESContext *esContext, unsigned char, int, int )
{
    zframework* framework = (zframework*) esContext->userData;
    framework->input();
}

int main ( int argc, char *argv[] )
{
    linux_resource resource;
    zframework framework(&resource);

    ESContext esContext;

    esInitContext ( &esContext );
    esContext.userData = &framework;

    esCreateWindow ( &esContext, "ZeptoBird", 568, 320, ES_WINDOW_RGB );

    if ( !Init ( &esContext ) )
        return 0;

    esRegisterDrawFunc ( &esContext, Draw );
    esRegisterKeyFunc ( &esContext, Input );

    esMainLoop ( &esContext );
}
