#import <UIKit/UIKit.h>
#include <common/zinput.h>

@interface GLViewController : UIViewController
{
}

- (void)initialize;
- (void)installWidth:(int)width andHeight:(int)height;
- (void)uninstall;

- (void)draw;
- (void)input:(touch_event)type withX:(int)x andY:(int)y;

- (void)pause;

@end
