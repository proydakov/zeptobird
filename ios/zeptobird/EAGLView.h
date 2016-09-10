#import <UIKit/UIKit.h>

@class GLViewController;

@interface EAGLView : UIView
{
}

@property (nonatomic, retain) IBOutlet GLViewController *controller;
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

@end
