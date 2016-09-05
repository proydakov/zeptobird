#import <UIKit/UIKit.h>

@interface GLViewController : UIViewController
{
}

- (void)initialize;
- (void)installWidth:(int)width andHeight:(int)height;
- (void)uninstall;

- (void)draw;
- (void)input;

- (void)pause;

@end
