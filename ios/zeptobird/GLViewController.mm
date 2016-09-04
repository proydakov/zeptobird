#import "GLViewController.h"
#import "GLView.h"

#include "ios_resource.h"

#include <iostream>
#include <render/zgles2_render.h>

@interface GLViewController ()
{
    ios_resource  resource;
    zgles2_render render;
}
@end

@implementation GLViewController

- (void)installWidth:(int)width andHeight:(int)height
{
    self->render.init(&resource, width, height);
}

- (void)uninstall
{
    self->render.deinit();
}

- (void)draw
{
    self->render.render();
}

- (void)input
{
    std::cout << "input" << std::endl;
    self->render.input();
}

-(UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

-(void)viewDidLoad
{
    std::cout << "load" << std::endl;
}

-(void)viewDidUnload
{
    std::cout << "unload" << std::endl;
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)dealloc 
{
}

@end
