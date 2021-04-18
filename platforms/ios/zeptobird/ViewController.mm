#import "ViewController.h"

#include "ios_sound.h"
#include "ios_resource.h"

#include <memory>
#include <iostream>
#include <platform/zplatform.h>
#include <framework/zframework.h>

@interface ViewController ()
{
    ios_sound    sound;
    ios_resource resource;

    std::unique_ptr<zframework> framework;

    int lastw;
    int lasth;
    bool pause;
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    [self setupGL];
}

- (void)dealloc
{
    [self tearDownGL];

    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;

        [self tearDownGL];

        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];

    zplatform platform(sound, resource);
    self->lastw = 1280;
    self->lasth = 1024;
    self->pause = false;
    self->framework.reset(new zframework( platform, self->lastw, self->lasth ));
}

- (void)tearDownGL
{
    self->framework.reset();
}

- (void)update
{
    if (self->pause)
    {
        return;
    }
    self->framework->update();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    bool updated = false;
    if (self->lastw != view.drawableWidth)
    {
        self->lastw = view.drawableWidth;
        updated = true;
    }
    if (self->lasth != view.drawableHeight)
    {
        self->lasth = view.drawableHeight;
        updated = true;
    }
    if (updated)
    {
        self->framework->resize(self->lastw, self->lasth);
    }
    self->framework->render();
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *aTouch = [touches anyObject];
    CGPoint position = [aTouch locationInView:self.view];
    [self input: touch::began withX:position.x andY:position.y];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *aTouch = [touches anyObject];
    CGPoint position = [aTouch locationInView:self.view];
    [self input: touch::move withX:position.x andY:position.y];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *aTouch = [touches anyObject];
    CGPoint position = [aTouch locationInView:self.view];
    [self input: touch::end withX:position.x andY:position.y];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
}

- (void)input:(touch)type withX:(int)x andY:(int)y;
{
    x = x * 2;
    y = y * 2;
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
    std::cout << "pause" << std::endl;
    self->framework->pause();
    self->pause = true;
}

- (void)resume
{
    std::cout << "resume" << std::endl;
    self->pause = false;
}

@end
