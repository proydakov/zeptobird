#import <UIKit/UIKit.h>

enum touch {
    began,
    move,
    end
};

@interface GLViewController : UIViewController
{
}

- (void)initialize;
- (void)installWidth:(int)width andHeight:(int)height;
- (void)uninstall;

- (void)draw;
- (void)input:(touch)type withX:(int)x andY:(int)y;

- (void)pause;

@end
