#import "GLViewController.h"
#import "EAGLView.h"

#include "ios_sound.h"
#include "ios_resource.h"

#include <memory>
#include <iostream>
#include <framework/zframework.h>
#include <platform/zplatform.h>

@interface GLViewController ()
{
    ios_sound    sound;
    ios_resource resource;

    std::unique_ptr<zframework> framework;
}
@end

@implementation GLViewController

- (void)initialize
{
    zplatform platform(&sound, &resource);
    framework.reset(new zframework( platform ));
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

- (void)input:(touch)type withX:(int)x andY:(int)y;
{
    switch (type) {
        case began:
            self->framework->input(touch_event::began, x, y);
            break;

        case move:
            self->framework->input(touch_event::move, x, y);
            break;

        case end:
            self->framework->input(touch_event::end, x, y);
            break;
    }
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
