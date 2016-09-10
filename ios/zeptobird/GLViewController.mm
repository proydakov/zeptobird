#import "GLViewController.h"
#import "EAGLView.h"

#include "ios_resource.h"

#include <memory>
#include <iostream>
#include <framework/zframework.h>

@interface GLViewController ()
{
    ios_resource                resource;
    std::unique_ptr<zframework> framework;
}
@end

@implementation GLViewController

- (void)initialize
{
    framework.reset(new zframework(&resource));
}

- (void)dealloc
{
}

- (void)installWidth:(int)width andHeight:(int)height
{
    self->framework->init(width, height);
}

- (void)uninstall
{
    self->framework->deinit();
}

- (void)draw
{
    self->framework->update();
    self->framework->render();
}

- (void)input
{
    self->framework->input();
}

- (void)pause
{
    self->framework->pause();
}

-(UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

-(void)viewDidLoad
{
    std::cout << "GLViewController:load" << std::endl;
}

-(void)viewDidUnload
{
    std::cout << "GLViewController:unload" << std::endl;
}

@end
