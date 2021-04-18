#import <GLKit/GLKit.h>

enum touch {
    began,
    move,
    end
};

@interface ViewController : GLKViewController

- (void)input:(touch)type withX:(int)x andY:(int)y;

- (void)pause;
- (void)resume;

@end
