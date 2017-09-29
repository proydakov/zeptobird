//
//  AppDelegate.h
//  zeptobird
//
//  Created by Evgeny Proydakov on 03.09.16.
//  Copyright © 2016 proydakov. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GLViewController;

@interface AppDelegate : NSObject <UIApplicationDelegate>
{
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet GLViewController *rootController;

@end
