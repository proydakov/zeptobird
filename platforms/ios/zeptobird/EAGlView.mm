#include <iostream>

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "EAGLView.h"
#import "GLViewController.h"

@interface EAGLView ()
{
    GLint  backingWidth;
    GLint  backingHeight;
    GLuint frameBuffer;
    GLuint renderBuffer;
    GLuint depthBuffer;

    bool   generated;
}
@property (nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, retain) CADisplayLink *displayLink;
- (void)drawView;
@end

@implementation EAGLView
@synthesize controller, animating, context, animationFrameInterval, displayLink;
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithCoder:(NSCoder*)coder
{
    if (self = [super initWithCoder:coder])
    {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        eaglLayer.opaque = YES;

        EAGLContext *theContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        self.context = theContext;

        if (!self.context || ![EAGLContext setCurrentContext:self.context])
        {
            return nil;
        }
        animating = NO;
        animationFrameInterval = 1;
    }
    return self;
}

- (void)createBuffers
{
    glGenFramebuffers(1, &frameBuffer);
    glGenRenderbuffers(1, &renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
}

- (void)destroyBuffers
{
    glDeleteFramebuffers(1, &frameBuffer);
    frameBuffer = 0;
    glDeleteRenderbuffers(1, &renderBuffer);
    renderBuffer = 0;

    if(depthBuffer)
    {
        glDeleteRenderbuffers(1, &depthBuffer);
        depthBuffer = 0;
    }
}

- (void)drawView
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    [controller draw];

    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)layoutSubviews
{
    if(generated) {
        return;
    }
    generated = true;
    [EAGLContext setCurrentContext:context];
    [self destroyBuffers];
    [self createBuffers];

    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);

    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    [controller installWidth: backingWidth andHeight: backingHeight];

    [self drawView];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *aTouch = [touches anyObject];
    CGPoint position = [aTouch locationInView:self];
    [controller input: touch::began withX:position.x andY:position.y];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *aTouch = [touches anyObject];
    CGPoint position = [aTouch locationInView:self];
    [controller input: touch::move withX:position.x andY:position.y];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *aTouch = [touches anyObject];
    CGPoint position = [aTouch locationInView:self];
    [controller input: touch::end withX:position.x andY:position.y];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView)];
        [displayLink setPreferredFramesPerSecond:animationFrameInterval];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        animating = YES;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        [displayLink invalidate];
        self.displayLink = nil;

        animating = NO;
    }
}

- (void)dealloc
{
    [controller uninstall];
    controller = nil;

    if (frameBuffer)
    {
        glDeleteFramebuffers(1, &frameBuffer);
        frameBuffer = 0;
    }
    if (renderBuffer)
    {
        glDeleteRenderbuffers(1, &renderBuffer);
        renderBuffer = 0;
    }
    if (depthBuffer)
    {
        glDeleteRenderbuffers(1, &depthBuffer);
        depthBuffer = 0;
    }

    if ([EAGLContext currentContext] == self.context)
        [EAGLContext setCurrentContext:nil];
    context = nil;

    [displayLink invalidate];
    displayLink = nil;
}

@end
